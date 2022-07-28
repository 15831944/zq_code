#include <iostream>
#include <Winsock2.h>
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

	POINT p1 = {0, 0}, p2 = {9, 9};

	//ҵ��ѭ��
	while (1)
	{
		system("cls");
		for (int i = 0; i < 100; ++i)
		{
			if (i == p1.x + p1.y * 10)
				std::cout<<"��";
			else if (i == p2.x + p2.y * 10)
				std::cout<<"��";
			else
				std::cout<<"��";
			if (i % 10 == 9)
				std::cout<<std::endl;
		}

		int r = recv(c, (char*)&p2, sizeof(p2), 0);

		int x = p1.x;
		int y = p1.y;
		if ((::GetAsyncKeyState('W') & 1) && p1.y > 0)
			p1.y -= 1;
		if ((::GetAsyncKeyState('S') & 1) && p1.y < 9)
			p1.y += 1;
		if ((::GetAsyncKeyState('A') & 1) && p1.x > 0)
			p1.x -= 1;
		if ((::GetAsyncKeyState('D') & 1) && p1.x < 9)
			p1.x += 1;
		if (p1.x != x || p1.y != y)
			send(c, (const char*)&p1, sizeof(p1), 0);

		Sleep(20);
	}

	closesocket(s_listen);
	WSACleanup();

	system("pause");
}