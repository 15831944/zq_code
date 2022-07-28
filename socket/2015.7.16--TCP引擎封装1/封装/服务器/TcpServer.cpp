#include "TcpServer.h"
#pragma comment(lib, "Ws2_32.lib")

#define _CS_CONNECTED			0 //�ͻ���״̬������
#define _CS_PREPARE_DISCONNECT	1 //�ͻ���״̬��׼�������Ͽ�
#define _CS_BE_DISCONNECTED		2 //�ͻ���״̬�������Ͽ�
#define _CS_WAIT_FINISH			3 //�ͻ���״̬���ȴ��Է�����

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
	m_BeginKA = beginka;
	m_IntervalKA = intervalka;

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
	
}

bool CTcpServer::GetNetEvent(_NET_EVENT* ne)
{
	if (!m_NetEvent.Empty())
	{
		m_NetEvent.Front(ne);
		m_NetEvent.Pop();
		return true;
	}
	else
		return false;
}

void CTcpServer::ReleaseNetEvent(_NET_EVENT* ne)
{
	if (ne->type == _NE_DATA)
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