#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	char server_ip[32];
	std::cout<<"�����������ip��ַ��";
	std::cin>>server_ip;

	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long no_blocking = TRUE;
	ioctlsocket(s, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	
	//��Ϊconnectһ������ʧ�����Դ˴������
	connect(s, (sockaddr*)&si, sizeof(si));

	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(s, &fs);
	select(0, 0, &fs, 0, 0);
	
	std::cout<<"���ӷ������ɹ���"<<std::endl;

	//ҵ��ѭ��
	while (1)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			closesocket(s);
			break;
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			shutdown(s, SD_SEND);
			break;
		}
		
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

	WSACleanup();

	system("pause");
}