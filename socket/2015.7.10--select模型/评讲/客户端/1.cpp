#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(0x0101, &wd);
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char server_ip[256];
	std::cout<<"�����������ip��ַ��";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
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
		//����Ҫ���͵��ļ�����
		std::cout<<"������Ҫ���͵��ļ�·����";
		char filename[256];
		std::cin>>filename;
		FILE* pf = 0;
		fopen_s(&pf, filename, "rb");
		if (!pf)
		{
			std::cout<<"�޷���ָ���ļ���";
			system("pause");
			continue;
		}
		fseek(pf, 0, SEEK_END);
		int fs = ftell(pf);
		rewind(pf);
		char* fd = (char*)malloc(fs);
		fread(fd, 1, fs, pf);
		fclose(pf);

		//�����ȷ��͵���������һ����˵
		//����4�ֽ�������С��������û��
		//���⣬�����϶����Է��ͳɹ�����
		//�����Ҫ���ͽϴ�����ݣ����ǻ�
		//����Ҫ���send�ķ���ֵ��ȷ����
		//�͵�ʵ���ֽ���
		send(s_server, (const char*)&fs, sizeof(int), 0);

		//�����ļ�����
		int send_byte = 0; //�ѷ����ֽ���
		while (send_byte < fs)
		{
			//send�����������͵������ֽ���
			int r = send(
				s_server,
				fd + send_byte,
				(fs - send_byte) > 8192 ? 8192 : fs - send_byte,
				0);
			send_byte += r;
			std::cout<<"��ǰ�Ѿ�������"<<send_byte<<"���ֽ�";
		}

		free(fd);
	}

	closesocket(s_server);
	WSACleanup();

	system("pause");
}