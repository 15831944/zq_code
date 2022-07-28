#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

void main()
{
	WORD wVer = MAKEWORD(SOCK_VERH, SOCK_VERL);
	WSADATA wd;
	int err = ::WSAStartup(wVer, &wd);
	if (0 != err)
	{
		cout << "�޷���ʼ��Socket2ϵͳ����!" << endl;
		system("pause");
		return;
	}
	if (LOBYTE(wd.wVersion) != SOCK_VERL ||
		HIBYTE(wd.wVersion) != SOCK_VERH)
	{
		cout << "�޷���ʼ��" << SOCK_VERH << "." << SOCK_VERL << "�汾��Socket����!" << endl;
		system("pause");
		WSACleanup();
		return;
	}
	//�����׽���
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	if (-1 == bind(sListen, (sockaddr*)&si, sizeof(si)))
	{
		cout << "�׽������ַ��ʧ�ܣ�" << endl;
		system("pause");
		closesocket(sListen);
		WSACleanup();
		return;
	}

	if (-1 == listen(sListen, 8))
	{
		cout << "����ʧ�ܣ�" << endl;
		system("pause");
		closesocket(sListen);
		WSACleanup();
		return;
	}

	//�ͻ��׽���
	std::vector<SOCKET> client;
	cout << "�������Ѿ�������" << endl;
	while (1)
	{
		fd_set fs;
		FD_ZERO(&fs);
		FD_SET(sListen, &fs);

		for (int i = 0; i < client.size(); ++i)
			FD_SET(client.at(i), &fs);
		timeval t = { 2.0 };
		select(0, &fs, 0, 0, &t);

		for (int i = 0; i < fs.fd_count; ++i)
		{
			if (fs.fd_array[i] == sListen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(sListen, (sockaddr*)&ci, &ci_len);
				cout << inet_ntoa(ci.sin_addr) << "���ӵ�������,�׽���Ϊ��" << c << endl;
				client.push_back(c);
			}
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i], buf, 256, 0);
				if (r == 0 || r == SOCKET_ERROR)
				{
					cout << fs.fd_array[i] << "�뿪�˷�����" << endl;
					char buf1[256] = {};
					sprintf_s(buf1, "%d�뿪�˷�����", fs.fd_array[i], buf);
					for (int j = 0; j < client.size(); ++j)
					{
						if (fs.fd_array[j] != client.at(j))
							send(client[j], buf1, strlen(buf1) + 1, 0);
					}
					for (int j = 0; j < client.size(); ++j)
					{
						if (fs.fd_array[i] == client.at(j))
						{
							client.erase(client.begin() + j);
							break;
						}
					}
				}
				else
				{
					cout << fs.fd_array[i] << "˵:" << buf << endl;

					char buf1[256] = {};
					sprintf_s(buf1, "\n%d˵��%s", fs.fd_array[i], buf);
					for (int j = 0; j < client.size(); ++j)
					{
						if (fs.fd_array[i] != client[j])
							send(client[j], buf1, strlen(buf1) + 1, 0);
					}
				}
			}
		}
	}
	for (int i = 0; i < client.size(); ++i)
		closesocket(client[i]);
	closesocket(sListen);
	WSACleanup();
	system("pause");
}