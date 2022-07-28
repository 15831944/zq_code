#include <iostream>
#include <Winsock2.h>
#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

char buf[1024 * 1024 * 32];

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long no_blocking = TRUE;
	ioctlsocket(s, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	//��Ϊconnectһ������ʧ�����Դ˴������
	connect(s, (sockaddr*)&si, sizeof(si));

	//��һ��ʱ��֮�ڼ���׽��ֿ�д�������д
	//�����ӳɹ�������Ϊ�˷��㴦���һֱ�ȴ�
	//ֱ����Ϊ��д
	fd_set fs;
	FD_ZERO(&fs);
	FD_SET(s, &fs);
	select(0, 0, &fs, 0, 0);

	std::cout<<"���ӷ������ɹ���"<<std::endl;

	CNetWork nw(s);

	//ҵ��ѭ��
	while (1)
	{
		//����
		if (!nw.Run())
			break;

		system("cls");
		std::cout<<"������Ҫ���͵�MB��";
		int send_mb;
		std::cin>>send_mb;
		send_mb *= 1024 * 1024;

		nw.SendData(buf, send_mb);

		Sleep(20);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}