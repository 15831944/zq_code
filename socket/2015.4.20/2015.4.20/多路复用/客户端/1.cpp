#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	//1���������绷��
	//2�������׽���
	//3�����ݷ�����IP��ַ����ַ��Ϣ�ṹ��
	//4��ͨ���׽��ֺ͵�ַ��Ϣ�ṹ���������ӷ�����
	//5��ҵ��ѭ��
	//6���ر��׽���
	//7���ر����绷��

	 //1���������绷��
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	//2�������׽���
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3�����ݷ�����IP��ַ����ַ��Ϣ�ṹ��
	char server_ip[256];
	std::cout<<"�������������IP��ַ��";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip); //������IP��ַ

	//4��ͨ���׽��ֺ͵�ַ��Ϣ�ṹ���������ӷ�����
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"�޷����ӷ�������";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	//5��ҵ��ѭ��
	while (1)
	{
		char buf[256];
		std::cout<<"������Ҫ���͵��ַ�����";
		std::cin>>buf;

		//�������ݵ�������
		send(
			sServer, //��Ӧ�������������׽���
			buf, //�������ݵ��ڴ��ַ
			strlen(buf) + 1, //�������ݵ��ڴ泤��
			0);

		//������͵���quit���˳�����
		if (strcmp(buf, "quit") == 0)
			break;
	}

	//6���ر��׽���
	closesocket(sServer);

	//7���ر����绷��
	WSACleanup();

	system("pause");
}