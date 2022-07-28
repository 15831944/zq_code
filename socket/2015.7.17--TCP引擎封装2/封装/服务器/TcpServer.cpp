#include "TcpServer.h"
#include <MSTcpIP.h>
#pragma comment(lib, "Ws2_32.lib")

#define _CS_CONNECTED			0 //�ͻ���״̬������
#define _CS_PREPARE_DISCONNECT	1 //�ͻ���״̬��׼�������Ͽ�
#define _CS_BE_DISCONNECTED		2 //�ͻ���״̬�������Ͽ�
#define _CS_WAIT_FINISH			3 //�ͻ���״̬���ȴ��Է�����

bool CTcpServer::_Accept()
{
	//���������־Ϊ���ҵ�ǰ��ͻ�������δ�����������
	if (m_Continue && m_Client.Size() < m_MaxClient)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		SOCKET s = accept(m_Listen, (sockaddr*)&ci, &ci_len);
		if (s == INVALID_SOCKET)
		{
			//���������Ĵ���
			if (WSAGetLastError() != WSAEWOULDBLOCK)
				return false;
		}
		else
		{
			//��ʼ���ͻ�����
			_CLIENT client;
			client.state = _CS_CONNECTED;
			client.ip = ci.sin_addr.S_un.S_addr;
			client.rd.Clear();

			//��������������ʱ��
			BOOL b = TRUE;
			setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (const char*)&b, sizeof(b));
			DWORD dw;
			tcp_keepalive tka = {1, m_BeginKA, m_IntervalKA};
			WSAIoctl(s, SIO_KEEPALIVE_VALS, &tka, sizeof(tka), 0, 0, &dw, 0, 0);

			//װ��ͻ���
			m_Client.Insert(s, client);

			//Ͷ�������¼�
			_SNET_EVENT ne = {_SNE_CONNECTED, s, client.ip, 0, 0};
			m_SNetEvent.Push(ne);
		}
	}

	return true;
}

void CTcpServer::_Send()
{
	//ѭ��ÿ����ҽ��з���
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);

		//���ͻ�״̬���ǵȴ��Է�����״̬������²ſ��Է�������
		if (pair->data.state != _CS_WAIT_FINISH)
		{
			//�˳������ѭ��ʱ�����
			//0����ʾû��Ҫ���͵�������
			//1����ʾ��ʱ���ܷ���
			//2����ʾ���ʹ���
			int quit_state = 0;

			//�����в�Ϊ��
			while (!pair->data.sd_queue.Empty())
			{
				//�õ�Ҫ���͵�����
				_SEND_DATA sd;
				pair->data.sd_queue.Front(&sd);

				//ѭ������
				while (sd.send_size < sd.all_size)
				{
					int r = send(pair->key, sd.data + sd.send_size, sd.all_size - sd.send_size, 0);
					if (r == SOCKET_ERROR)
					{
						//��ĳ���
						if (WSAEWOULDBLOCK != WSAGetLastError())
							quit_state = 2;
						else
							quit_state = 1;
						break;
					}
					else
						sd.send_size += r;
				}

				//�����˳�����ѭ����״̬��������
				if (0 == quit_state)
				{
					m_MP.Free(sd.data);
					pair->data.sd_queue.Pop();
				}
				else
					break;
			}

			switch (quit_state)
			{
			case 0: //û��Ҫ���͵�������
				{
					if (pair->data.state == _CS_PREPARE_DISCONNECT)
					{
						shutdown(pair->key, SD_SEND);
						pair->data.state = _CS_WAIT_FINISH;
					}
					else if (pair->data.state == _CS_BE_DISCONNECTED)
					{
						shutdown(pair->key, SD_SEND);
						_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_C);
						--i;
					}
					break;
				}
			case 1: //��ʱ���ܷ���
				{
					break;
				}
			case 2: //������
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_E);
					--i;
					break;
				}
			}
		}
	}
}

void CTcpServer::_Recv()
{
	//�������ݵĻ���
	char buf[65536];

	//ѭ��ÿ����ҽ��н���
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		//�õ���ǰ�����Ϣ
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);

		//�����״̬��Ϊ�����Ͽ���ʱ����Խ��н���
		if (pair->data.state != _CS_BE_DISCONNECTED)
		{
			//��������
			int r = recv(pair->key, buf, 65536, 0);

			//���������
			if (r == SOCKET_ERROR)
			{
				//��ĳ���
				if (WSAEWOULDBLOCK != WSAGetLastError())
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_E);
					--i;
				}
			}
			//�Է�������shutdown
			else if (r == 0)
			{
				//���״̬������״̬��׼�������Ͽ�״̬����ֻ��ת��״̬�������Ͽ�
				if (pair->data.state == _CS_CONNECTED || pair->data.state == _CS_PREPARE_DISCONNECT)
					pair->data.state = _CS_BE_DISCONNECTED;
				//���״̬�ǵȴ��Է�����״̬����ر��׽���
				else
				{
					_CloseClient(pair->key, &pair->data, _SNE_DISCONNECTED_S);
					--i;
				}
			}
			else
				_RecvClient(buf, r, pair->key, &pair->data);
		}
	}
}

void CTcpServer::_RecvClient(char* buf, int r, SOCKET s, _CLIENT* c)
{
	//��ʼ��������λ��
	int cur = 0;

	//ѭ��������������
	while (cur < r)
	{
		//��ǰû�����곤��
		if (c->rd.len_valid_bytes < 4)
		{
			//��ǰ�������곤��
			if (4 - c->rd.len_valid_bytes > r - cur)
			{
				//���������յĳ����ֽڵ��ܳ�����
				memcpy(
					(char*)&c->rd.all_len + c->rd.len_valid_bytes,
					buf + cur,
					r - cur);

				//���ȵ���Ч�ֽ�������
				c->rd.len_valid_bytes += r - cur;

				//������λ�õ������������˳�ѭ�������������ݣ�
				cur += r - cur;
			}
			//��ǰ�������곤��
			else
			{
				//���������յĳ����ֽڵ��ܳ�����
				memcpy(
					(char*)&c->rd.all_len + c->rd.len_valid_bytes,
					buf + cur,
					4 - c->rd.len_valid_bytes);

				//������λ�õ���
				cur += 4 - c->rd.len_valid_bytes;

				//���ȵ���Ч�ֽ�������
				c->rd.len_valid_bytes = 4;

				//���ٽ������ݵ��ڴ�
				c->rd.data = (char*)m_MP.Allocate(c->rd.all_len);
			}
		}
		//��ǰ�����˳���Ӧ��������
		else
		{
			//��ǰ������������
			if (c->rd.all_len - c->rd.recv_len > r - cur)
			{
				//���������յ����ݵ���������
				memcpy(
					c->rd.data + c->rd.recv_len,
					buf + cur,
					r - cur);

				//�Ѿ����յ����ݸ���
				c->rd.recv_len += r - cur;

				//������λ�õ������������˳�ѭ�������������ݣ�
				cur += r - cur;
			}
			//��ǰ������������
			else
			{
				//���������յ����ݵ���������
				memcpy(
					c->rd.data + c->rd.recv_len,
					buf + cur,
					c->rd.all_len - c->rd.recv_len);

				//������λ�õ���
				cur += c->rd.all_len - c->rd.recv_len;

				//�����һ�����ķ���Ͷ�ݽ������������¼�
				_SNET_EVENT ne = {_SNE_DATA, s, c->ip, c->rd.data, c->rd.all_len};
				m_SNetEvent.Push(ne);

				//���
				c->rd.Clear();
			}
		}
	}
}

void CTcpServer::_CloseClient(SOCKET s, _CLIENT* c, int t)
{
	//�ͷŽ�������
	if (c->rd.data)
		m_MP.Free(c->rd.data);

	//�ͷŷ�������
	while (!c->sd_queue.Empty())
	{
		_SEND_DATA sd;
		c->sd_queue.Front(&sd);
		c->sd_queue.Pop();
		m_MP.Free(sd.data);
	}

	//�ر��׽���
	closesocket(s);

	//�ӿͻ�����ɾ��
	m_Client.Erase(s);

	//Ͷ���¼�
	_SNET_EVENT ne = {t, s, c->ip, 0, 0};
	m_SNetEvent.Push(ne);
}

CTcpServer::CTcpServer()
:
m_Listen(INVALID_SOCKET),
m_MaxClient(0),
m_BeginKA(0),
m_IntervalKA(0),
m_Continue(false)
{}

CTcpServer::~CTcpServer()
{}

bool CTcpServer::Init(unsigned short port,
					  int maxclient,
					  int beginka,
					  int intervalka)
{
	//�������
	if (port < _MIN_PORT || maxclient < 1 || beginka < 1 || intervalka < 1)
		return false;

	//�õ�����
	m_MaxClient = maxclient;
	m_BeginKA = beginka * 1000;
	m_IntervalKA = intervalka * 1000;

	//�������绷��
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//���������׽��ֲ�����Ϊ������ģʽ
	m_Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Listen, FIONBIO, &no_blocking);

	//����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	//���׽��ֺ͵�ַ��Ϣ�ṹ��
	bind(m_Listen, (sockaddr*)&si, sizeof(si));

	//�����׽���Ϊ����ģʽ
	listen(m_Listen, 8);

	//���ó�����־Ϊ��
	m_Continue = true;

	return true;
}

void CTcpServer::Run()
{
	_Accept();
	_Send();
	_Recv();
}

void CTcpServer::Stop()
{
	//���ó�����־Ϊ��
	m_Continue = false;

	//�������Ѿ����ӵĿͻ��������ŶϿ�
	for (int i = 0; i < m_Client.Size(); ++i)
	{
		CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.At(i);
		if (pair->data.state == _CS_CONNECTED)
			pair->data.state = _CS_PREPARE_DISCONNECT;
	}
}

bool CTcpServer::Continue()
{
	//���������Stop����û�����ӵ�����˲ŷ��ؼ�
	return m_Continue || m_Client.Size() > 0;
}

void CTcpServer::End()
{
	closesocket(m_Listen);
	WSACleanup();
}

bool CTcpServer::GetNetEvent(_SNET_EVENT* ne)
{
	if (!m_SNetEvent.Empty())
	{
		m_SNetEvent.Front(ne);
		m_SNetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpServer::ReleaseNetEvent(_SNET_EVENT* ne)
{
	if (ne->type == _SNE_DATA)
		m_MP.Free(ne->data);
}

bool CTcpServer::SendData(SOCKET s, const void* data, int len)
{
	CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.Find(s);

	//�����׽�����Ч����״̬����Ϊ����״̬���������Ҳ������Ч
	if (pair && pair->data.state == _CS_CONNECTED && data && len > 0)
	{
		_SEND_DATA _send_data;

		//��䷢�ͽṹ�����
		_send_data.all_size = sizeof(int) + len;
		_send_data.data = (char*)m_MP.Allocate(_send_data.all_size);
		*((int*)_send_data.data) = len;
		memcpy(_send_data.data + sizeof(int), data, len);
		_send_data.send_size = 0;

		//װ�뷢�Ͷ���
		pair->data.sd_queue.Push(_send_data);

		return true;
	}
	else
		return false;
}

bool CTcpServer::Disconnect(SOCKET s)
{
	CMap<SOCKET, _CLIENT>::PAIR* pair = m_Client.Find(s);

	//�����׽�����Ч����״̬����Ϊ����״̬
	if (pair && pair->data.state == _CS_CONNECTED)
	{
		pair->data.state = _CS_PREPARE_DISCONNECT;
		return true;
	}
	else
		return false;
}

char* CTcpServer::ulong_str(unsigned long ip, char* buf)
{
	in_addr ia;
	ia.S_un.S_addr = ip;
	char* p = inet_ntoa(ia);
	memcpy(buf, p, strlen(p) + 1);
	return buf;
}