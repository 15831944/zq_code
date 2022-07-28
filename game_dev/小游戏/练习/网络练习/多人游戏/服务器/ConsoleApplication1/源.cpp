#include <iostream>
#define FD_SETSIZE 256
#include <Winsock2.h>
#include <vector>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define MAP_W 20
#define MAP_H 20
#define MAP_S (MAP_W * MAP_H)

#define VIEW_W 9
#define VIEW_H 9

struct _CLIENT
{
	bool lianjie;
	bool lianjie1;
	bool shanchu;
	SOCKET s; //�׽���
	int x, y;
	char name[32];
};
std::vector<_CLIENT> clients; //�ͻ���

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1, 1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	int num = 0;
	const char* name1[] = { "aa", "bb", "cc", "dd" };
	//ҵ��ѭ��
	while (1)
	{
		//�����׽��ּ���
		fd_set fs;

		//����׽��ּ���
		FD_ZERO(&fs);

		//װ�ؼ����׽���
		FD_SET(s_listen, &fs);

		//װ�������׽���
		for (int i = 0; i < (int)clients.size(); ++i)
			FD_SET(clients[i].s, &fs);

		//��·����
		timeval t = { 5, 500 };
		select(0, &fs, 0, 0, &t);

		//������о߱��ɶ��Ե��׽���
		for (int i = 0; i < (int)fs.fd_count; ++i)
		{
			//����ǰ�߱��ɶ��Ե��׽����Ǽ����׽���
			if (fs.fd_array[i] == s_listen )
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(s_listen, (sockaddr*)&ci, &ci_len);
				std::cout << inet_ntoa(ci.sin_addr) << "���ӵ�������" << std::endl;
				_CLIENT client;
				client.lianjie = true;
				client.lianjie1 = true;
				client.shanchu = false;
				client.s = c;
				client.x = VIEW_W / 2;
				client.y = VIEW_H / 2;
				strcpy_s(client.name, 32, name1[num++]);
				clients.push_back(client);
				for (int j = 0; j < clients.size(); ++j)
				{
					clients[j].lianjie1 = true;
					send(c, (char*)&clients[j], sizeof(client), 0);
					if (c != clients[j].s)
					{
						send(clients[j].s, (char*)&client, sizeof(client), 0);
					}
				}
			}
			//����ǰ�߱��ɶ��Ե��׽����������׽���
			else
			{
				_CLIENT client;
				int r = recv(fs.fd_array[i], (char*)&client, sizeof(_CLIENT), 0);
				if (r == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						int j;
						for (j = 0; j < clients.size(); ++j)
						{
							if (fs.fd_array[i] == clients[j].s)
								break;
						}
						for (int k = 0; k < clients.size(); ++k)
						{
							if (clients[k].s != fs.fd_array[i])
							{
								client.shanchu = true;
								strcpy_s(client.name, 32, clients[j].name);
								send(clients[k].s, (char*)&client, sizeof(client), 0);
							}
						}
						closesocket(clients[j].s);
						clients.erase(clients.begin() + j);
					}	
				}
				else
				{
					for (int j = 0; j < clients.size(); ++j)
					{
						if (fs.fd_array[i] == clients[j].s)
						{
							clients[j].x = client.x;
							clients[j].y = client.y;
							strcpy_s(client.name, 32, clients[j].name);
							client.s = fs.fd_array[i];
							break;
						}
					}

					for (int j = 0; j < clients.size(); ++j)
					{
						//if ((fs.fd_array[i] != clients[j].s))
							send(clients[j].s, (char*)&client, sizeof(client), 0);
					}
				}
			}
		}

		std::cout << "��ǰ��" << clients.size() << "����ң�" << std::endl;
	}

	//�ر��׽���
	closesocket(s_listen);

	//�ر����绷��
	WSACleanup();

	system("pause");
}