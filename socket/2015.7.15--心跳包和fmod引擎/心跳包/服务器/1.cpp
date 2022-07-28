#include <iostream>
#include <Winsock2.h>
#include <MSTcpIP.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	SOCKET s;

	//��������
	while (1)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		s = accept(s_listen, (sockaddr*)&ci, &ci_len);
		if (s == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout<<"�����������Ĵ���";
				system("pause");
				break;
			}
		}
		else
			break;
	}

	std::cout<<"�пͻ������ӳɹ���"<<std::endl;

	//�����������ڼ��һ��TCP�����Ƿ񻹴���һ��
	//���ƣ����ڲ�����ʹ�÷������հ��ķ�ʽ���м��
	//�����԰�������������޷�ͨ����ͨ�ֶη��ֵ���
	//�ӶϿ��������������ߣ���һ����������������
	//��ôTCP�ڲ���ÿ��һ�ι̶�ʱ��ͷ�һ�����ݰ�
	//���Է����Է��յ����ݰ�֮��Ҳ��ط�һ�����ݰ�
	//��������������Ǵ�����ô�϶������յ��Է���
	//���İ����������ʧЧ����ô���ղ����Է��ط���
	//���ˣ�һ��ʱ��֮�ڻ�û���յ��Ļ���TCP���ж���
	//�������Ѿ�ʧЧ�ˣ���ô������recv����SOCKET_ERROR
	//���Ҵ�����WSAENETRESET

	//����������
	BOOL b = TRUE;
	setsockopt(
		s,
		SOL_SOCKET,
		SO_KEEPALIVE,
		(const char*)&b,
		sizeof(b));

	//������������ʱ��
	DWORD dw;
	tcp_keepalive tka
		=
	{
		1, //1��0��
		10 * 1000, //�����10���ڶ�û���յ��Է����͹��������ݣ���ô��ʼ���뷢����������״̬
		5 * 1000 //�ӷ���״̬ʱ�俪ʼ��ÿ��5�뷢��һ�����������м��
	};
	WSAIoctl(
		s,
		SIO_KEEPALIVE_VALS,
		&tka,
		sizeof(tka),
		0,
		0,
		&dw,
		0,
		0);

	//TCP��11��״̬��Ǩͼ�����һ��״̬WAIT_2_TIMES

	while (1)
	{
		char buf[256];
		int r = recv(s, buf, 256, 0);
		if (r == 0)
		{
			std::cout<<"���ŶϿ���"<<std::endl;
			break;
		}
		else if (r == SOCKET_ERROR)
		{
			if (WSAEWOULDBLOCK != WSAGetLastError())
			{
				std::cout<<"��������"<<std::endl;
				break;
			}
		}
		else
			std::cout<<"�յ�����"<<std::endl;

		Sleep(20);
	}

	closesocket(s);
	closesocket(s_listen);
	WSACleanup();

	system("pause");
}