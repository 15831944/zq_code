#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//�������ںͷ��������������շ��������׽���
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char server_ip[256];
	std::cout<<"�����������ip��ַ��";
	std::cin>>server_ip;

	//���һ����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);

	//�������ӷ�����
	if (SOCKET_ERROR == connect(s_server, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"�޷����ӷ�������";
		system("pause");
		closesocket(s_server);
		WSACleanup();
		return;
	}

	std::cout<<"�ɹ����ӷ�������"<<std::endl;

	//ҵ��ѭ��
	while (1)
	{
		char buf[256];
		std::cout<<"������Ҫ���͸����������ַ�����";
		std::cin>>buf;

		//��������
		send(
			s_server, //�����׽���
			buf, //���������ݵ��ڴ��׵�ַ
			strlen(buf) + 1, //���������ݵĳ���
			0); //��־����0����

		if (strcmp(buf, "exit") == 0)
			break;
	}

	//�ر��׽���
	closesocket(s_server);

	//�ر����绷��
	WSACleanup();

	system("pause");
}

//����ip��ַ��127.0.0.1