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
{}

void CTcpClient::_Recv()
{}

CTcpClient::CTcpClient()
:
m_Socket(INVALID_SOCKET),
m_State(_CS_NO_CONNECTED)
{}

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
	if (m_RD.data)
		m_MP.Free(m_RD.data);

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