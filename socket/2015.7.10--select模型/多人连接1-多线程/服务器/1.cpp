#include <iostream>
#include <Winsock2.h>
#include <process.h>
#pragma comment(lib, "Ws2_32.lib")

SOCKET client[256]; //�ͻ�����
int client_num = 0; //�ͻ�����

unsigned int _stdcall recv_client(void* p)
{
	//ҵ��ѭ��
	while (1)
	{
		char buf[256];
		recv(*((SOCKET*)p), buf, 256, 0);
		std::cout<<*((SOCKET*)p)<<"˵"<<buf<<std::endl;
	}

	return 1u;
}

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//���߳̽�������
	while (1)
	{
		sockaddr_in si_c;
		int len = sizeof(si_c);
		client[client_num] = accept(s_listen, (sockaddr*)&si_c, &len);
		std::cout<<inet_ntoa(si_c.sin_addr)<<"���ӵ�������"<<std::endl;
		//��4��������Ҫ����дһ����ַ�������
		//ַ�ᱻ������ʼ���̺߳�������ʽ����
		_beginthreadex(0, 0, recv_client, &client[client_num], 0, 0);
		client_num += 1;
	}

	//�ر��׽���
	closesocket(s_listen);

	//�ر����绷��
	WSACleanup();

	system("pause");
}