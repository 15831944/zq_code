#include <iostream>
#include <Winsock2.h>
#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���÷���������������ֻҪ�����׽�������Ϊ������
	//�ˣ���ô��������׽��ֵõ������������׽��ֶ���
	//�������ˣ�
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	SOCKET c;

	//�ȴ�����
	while (1)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		c = accept(s_listen, (sockaddr*)&ci, &ci_len);
		if (c == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout<<"��ĳ���";
				system("pause");
				closesocket(s_listen);
				WSACleanup();
				return;
			}
			else
			{
				std::cout<<"��ǰ�������ӣ�"<<std::endl;
				Sleep(1);
			}
		}
		else
			break;
	}

	std::cout<<"�ͻ������ӳɹ���"<<std::endl;

	CNetWork nw(c);

	//ҵ��ѭ��
	while (1)
	{
		//����
		if (!nw.Run())
			break;

		_RECV_DATA rd;
		while (nw.GetRecvDate(&rd))
		{
			std::cout<<"�յ�"<<rd.len<<"���ֽ�"<<std::endl;
			nw.ReleaseRecvData(&rd);
		}

		Sleep(20);
	}

	closesocket(s_listen);
	WSACleanup();

	system("pause");
}