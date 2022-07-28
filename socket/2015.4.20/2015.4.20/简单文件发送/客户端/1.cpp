#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

SOCKET sServer;

//��bool��ʾ�ɹ���ʧ��
bool file_send()
{
	//�õ��ļ���
	std::cout<<"�������ļ�����";
	char fn[256];
	std::cin>>fn;

	//���ļ�
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"�޷���ָ���ļ���";
		return true;
	}

	//�õ��ļ���С������
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = new char[strlen(fn) + 1 + fs];
	fread(fd + strlen(fn) + 1, 1, fs, pf);
	//strcpy_s(fd, strlen(fn) + 1 + fs, fn);
	memcpy(fd, fn, strlen(fn) + 1);
	fclose(pf);

	//�õ���ǰҪ���͵����ֽ���
	int all_bytes = strlen(fn) + 1 + fs;

	//�������ֽ�����������
	if (SOCKET_ERROR == send(sServer, (char*)&all_bytes, 4, 0))
		return false;

	//��������
	int cur_bytes = 0; //��ǰ�Ѿ����͵��ֽ���
	while (cur_bytes < all_bytes)
	{
		int r = send(sServer, fd + cur_bytes, all_bytes - cur_bytes, 0);
		if (r == SOCKET_ERROR)
			return false;
		else
			cur_bytes += r;
	}
	return true;
}

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char server_ip[256];
	std::cout<<"�������������IP��ַ��";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip); //������IP��ַ

	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"�޷����ӷ�������";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	while (1)
	{
		system("cls");
		std::cout<<"1)����\n2)�˳�\n��ѡ��";
		int sel;
		std::cin>>sel;
		if (sel == 1)
		{
			bool b = file_send();
			if (!b)
				break;
		}
		else if (sel == 2)
			break;

	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}