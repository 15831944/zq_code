#include "TcpClient.h"
#include <MSTcpIP.h>
#include <ctime>
#pragma comment(lib, "Ws2_32.lib")

#define _CS_NO_CONNECTED		0 //�ͻ���״̬��δ����
#define _CS_TRY_CONNECT			1 //�ͻ���״̬����������
#define _CS_CONNECTED			2 //�ͻ���״̬������
#define _CS_PREPARE_DISCONNECT	3 //�ͻ���״̬��׼�������Ͽ�
#define _CS_BE_DISCONNECTED		4 //�ͻ���״̬�������Ͽ�
#define _CS_WAIT_FINISH			5 //�ͻ���״̬���ȴ��Է�����

void CTcpClient::_Send()
{
	//���ͻ�״̬���ǵȴ��Է�����״̬������²ſ��Է�������
	if (m_State != _CS_NO_CONNECTED && m_State != _CS_TRY_CONNECT && m_State != _CS_WAIT_FINISH)
	{
		//�˳������ѭ��ʱ�����
		//0����ʾû��Ҫ���͵�������
		//1����ʾ��ʱ���ܷ���
		//2����ʾ���ʹ���
		int quit_state = 0;

		//�����в�Ϊ��
		while (!m_SDQueue.Empty())
		{
			//�õ�Ҫ���͵�����
			_SEND_DATA sd;
			m_SDQueue.Front(&sd);

			//ѭ������
			while (sd.send_size < sd.all_size)
			{
				int r = send(m_Socket, sd.data + sd.send_size, sd.all_size - sd.send_size, 0);
				if (r == SOCKET_ERROR)
				{
					//��ĳ���
					if (WSAEWOULDBLOCK != WSAGetLastError())
						quit_state = 2;
					//��ʱ���ܷ�����
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
				m_SDQueue.Pop();
			}
			else
				break;
		}

		switch (quit_state)
		{
		case 0: //û��Ҫ���͵�������
			{
				if (m_State == _CS_PREPARE_DISCONNECT)
				{
					shutdown(m_Socket, SD_SEND);
					m_State = _CS_WAIT_FINISH;
				}
				else if (m_State == _CS_BE_DISCONNECTED)
				{
					shutdown(m_Socket, SD_SEND);
					_CloseSocket(_CNE_DISCONNECTED_S);
				}
				break;
			}
		case 1: //��ʱ���ܷ���
			{
				break;
			}
		case 2: //������
			{
				_CloseSocket(_CNE_DISCONNECTED_E);
				break;
			}
		}
	}
}

void CTcpClient::_Recv()
{
	char buf[65536];

	//�����״̬��Ϊ�����Ͽ���ʱ����Խ��н���
	if (m_State != _CS_NO_CONNECTED && m_State != _CS_TRY_CONNECT && m_State != _CS_BE_DISCONNECTED)
	{
		//��������
		int r = recv(m_Socket, buf, 65536, 0);

		//���������
		if (r == SOCKET_ERROR)
		{
			//��ĳ���
			if (WSAEWOULDBLOCK != WSAGetLastError())
				_CloseSocket(_CNE_DISCONNECTED_E);
		}
		//�Է�������shutdown
		else if (r == 0)
		{
			//���״̬������״̬��׼�������Ͽ�״̬����ֻ��ת��״̬�������Ͽ�
			if (m_State == _CS_CONNECTED || m_State == _CS_PREPARE_DISCONNECT)
				m_State = _CS_BE_DISCONNECTED;
			//���״̬�ǵȴ��Է�����״̬����ر��׽���
			else
				_CloseSocket(_CNE_DISCONNECTED_C);
		}
		else
			_RecvData(buf, r);
	}
}

void CTcpClient::_RecvData(char* buf, int r)
{
	//��ʼ��������λ��
	int cur = 0;

	//ѭ��������������
	while (cur < r)
	{
		//��ǰû�����곤��
		if (m_RD.len_valid_bytes < 4)
		{
			//��ǰ�������곤��
			if (4 - m_RD.len_valid_bytes > r - cur)
			{
				//���������յĳ����ֽڵ��ܳ�����
				memcpy(
					(char*)&m_RD.all_len + m_RD.len_valid_bytes,
					buf + cur,
					r - cur);

				//���ȵ���Ч�ֽ�������
				m_RD.len_valid_bytes += r - cur;

				//������λ�õ������������˳�ѭ�������������ݣ�
				cur += r - cur;
			}
			//��ǰ�������곤��
			else
			{
				//���������յĳ����ֽڵ��ܳ�����
				memcpy(
					(char*)&m_RD.all_len + m_RD.len_valid_bytes,
					buf + cur,
					4 - m_RD.len_valid_bytes);

				//������λ�õ���
				cur += 4 - m_RD.len_valid_bytes;

				//���ȵ���Ч�ֽ�������
				m_RD.len_valid_bytes = 4;

				//���ٽ������ݵ��ڴ�
				m_RD.data = (char*)m_MP.Allocate(m_RD.all_len);
			}
		}
		//��ǰ�����˳���Ӧ��������
		else
		{
			//��ǰ������������
			if (m_RD.all_len - m_RD.recv_len > r - cur)
			{
				//���������յ����ݵ���������
				memcpy(
					m_RD.data + m_RD.recv_len,
					buf + cur,
					r - cur);

				//�Ѿ����յ����ݸ���
				m_RD.recv_len += r - cur;

				//������λ�õ������������˳�ѭ�������������ݣ�
				cur += r - cur;
			}
			//��ǰ������������
			else
			{
				//���������յ����ݵ���������
				memcpy(
					m_RD.data + m_RD.recv_len,
					buf + cur,
					m_RD.all_len - m_RD.recv_len);

				//������λ�õ���
				cur += m_RD.all_len - m_RD.recv_len;

				//�����һ�����ķ���Ͷ�ݽ������������¼�
				_CNET_EVENT ne = {_CNE_DATA, m_RD.data, m_RD.all_len};
				m_CNetEvent.Push(ne);

				//���
				m_RD.Clear();
			}
		}
	}
}

CTcpClient::CTcpClient()
:
m_Socket(INVALID_SOCKET),
m_State(_CS_NO_CONNECTED)
{
	m_RD.Clear();
}

CTcpClient::~CTcpClient()
{}

bool CTcpClient::ConnectIP(const char* ip,
						   unsigned short port,
						   int wait,
						   int beginka,
						   int intervalka)
{
	//�������
	if (m_State != _CS_NO_CONNECTED || !ip || port < _MIN_PORT || wait < 1 || beginka < 1 || intervalka < 1)
		return false;

	//�õ�����
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;
	m_Wait = wait;

	//��ʼ�����绷��
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//�����׽��ֲ����÷�����ģʽ
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Socket, FIONBIO, &no_blocking);

	//����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = inet_addr(ip);

	//��Ϊconnectһ������ʧ�����Դ˴������
	connect(m_Socket, (sockaddr*)&si, sizeof(si));

	//��¼��ǰʱ��
	m_ConnectTime = (int)time(0);

	//�޸�״̬Ϊ��������״̬
	m_State = _CS_TRY_CONNECT;

	return true;
}

bool CTcpClient::ConnectName(const char* name,
							 unsigned short port,
							 int wait,
							 int beginka,
							 int intervalka)
{
	//�������
	if (m_State != _CS_NO_CONNECTED || !name || port < _MIN_PORT || wait < 1 || beginka < 1 || intervalka < 1)
		return false;

	//�õ�����
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;
	m_Wait = wait;

	//��ʼ�����绷��
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//���������õ�IP��ַ��gethostbyname���Ǵ�
	//���������DNS�������и��ݴ��������ȥ��
	//��IP��ַ
	hostent* h = gethostbyname(name);
	if (0 == h)
	{
		//δ����
		WSACleanup();
		return false;
	}
	char* ip = inet_ntoa(*(in_addr*)h->h_addr_list[0]);
	//û����������ķ��������߷�����δ����
	if (0 == ip || 0 == strcmp(ip, "0.0.0.0"))
	{
		WSACleanup();
		return false;
	}

	//�����׽��ֲ����÷�����ģʽ
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(m_Socket, FIONBIO, &no_blocking);

	//����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(port);
	si.sin_addr.S_un.S_addr = inet_addr(ip);

	//��Ϊconnectһ������ʧ�����Դ˴������
	connect(m_Socket, (sockaddr*)&si, sizeof(si));

	//��¼��ǰʱ��
	m_ConnectTime = (int)time(0);

	//�޸�״̬Ϊ��������״̬
	m_State = _CS_TRY_CONNECT;

	return true;
}

void CTcpClient::Run()
{
	switch (m_State)
	{
	case _CS_NO_CONNECTED: break;
	case _CS_TRY_CONNECT:
		{
			fd_set fs;
			FD_ZERO(&fs);
			FD_SET(m_Socket, &fs);
			timeval t = {0, 0};
			select(0, 0, &fs, 0, &t);

			//�߱��ɶ��Ծ���ζ�����ӳɹ�
			if (1 == fs.fd_count)
			{
				//����״̬Ϊ����״̬
				m_State = _CS_CONNECTED;

				//��������������ʱ��
				BOOL b = TRUE;
				setsockopt(m_Socket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&b, sizeof(b));
				DWORD dw;
				tcp_keepalive tka = {1, m_BeginKA, m_IntervalKA};
				WSAIoctl(m_Socket, SIO_KEEPALIVE_VALS, &tka, sizeof(tka), 0, 0, &dw, 0, 0);

				//Ͷ�����ӳɹ��¼�
				_CNET_EVENT ne = {_CNE_CONNECT_OK, 0, 0};
				m_CNetEvent.Push(ne);
			}
			//���߱��ɶ��Ծ���ζ�Ż�û�����ӳɹ�
			else
			{
				//���ӳ�ʱ
				if (time(0) - m_ConnectTime > m_Wait)
					_CloseSocket(_CNE_CONNECT_FAIL);
			}

			break;
		}
	case _CS_CONNECTED:
	case _CS_PREPARE_DISCONNECT:
	case _CS_BE_DISCONNECTED:
	case _CS_WAIT_FINISH:
		{
			_Send();
			_Recv();
			break;
		}
	}
}

void CTcpClient::_CloseSocket(int t)
{
	//�ͷŽ�������
	if (m_RD.data)
		m_MP.Free(m_RD.data);

	//�ͷŷ�������
	while (!m_SDQueue.Empty())
	{
		_SEND_DATA sd;
		m_SDQueue.Front(&sd);
		m_SDQueue.Pop();
		m_MP.Free(sd.data);
	}

	//�ر��׽���
	closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;

	//�ر����绷��
	WSACleanup();

	//����״̬Ϊδ����״̬
	m_State = _CS_NO_CONNECTED;

	//Ͷ���¼�
	_CNET_EVENT ne = {t, 0, 0};
	m_CNetEvent.Push(ne);
}

bool CTcpClient::GetNetEvent(_CNET_EVENT* ne)
{
	if (!m_CNetEvent.Empty())
	{
		m_CNetEvent.Front(ne);
		m_CNetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpClient::ReleaseNetEvent(_CNET_EVENT* ne)
{
	if (ne->type == _CNE_DATA)
		m_MP.Free(ne->data);
}

bool CTcpClient::SendData(const void* data, int len)
{
	//��״̬����Ϊ����״̬���������Ҳ������Ч
	if (m_State == _CS_CONNECTED && data && len > 0)
	{
		_SEND_DATA _send_data;

		//��䷢�ͽṹ�����
		_send_data.all_size = sizeof(int) + len;
		_send_data.data = (char*)m_MP.Allocate(_send_data.all_size);
		*((int*)_send_data.data) = len;
		memcpy(_send_data.data + sizeof(int), data, len);
		_send_data.send_size = 0;

		//װ�뷢�Ͷ���
		m_SDQueue.Push(_send_data);

		return true;
	}
	else
		return false;
}

bool CTcpClient::Disconnect()
{
	//״̬����Ϊ����״̬
	if (m_State == _CS_CONNECTED)
	{
		m_State = _CS_PREPARE_DISCONNECT;
		return true;
	}
	else
		return false;
}