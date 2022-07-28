#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <vector>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define MAP_W 9
#define MAP_H 9
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

	std::cout << "���ӷ������ɹ���" << std::endl;

	int x = VIEW_W / 2;
	int y = VIEW_H / 2;

	//ҵ��ѭ��
	while (1)
	{
		system("cls");

		_CLIENT client;
		int r = recv(s, (char*)&client, sizeof(client), 0);
		if (r == SOCKET_ERROR)
		{
			
		}
		else
		{
			if (client.shanchu)
			{
				for (int i = 0; i < clients.size(); ++i)
				{
					if (strcmp(client.name, clients[i].name) == 0)
						clients.erase(clients.begin() + i);
				}
			}
			if (client.lianjie && client.lianjie1)
				clients.push_back(client);
			if (client.lianjie && !client.lianjie1)
			{
				for (int i = 0; i < clients.size(); ++i)
				{
					if (strcmp(client.name ,clients[i].name) == 0)
					{
						clients[i].x = client.x;
						clients[i].y = client.y;
					}
				}
			}
		}

		//����Ӣ��λ�õõ��ӿ����Ͻ�����ڴ��ͼ������
		int vx, vy;
		if (x < VIEW_W / 2)
			vx = 0;
		else if (x >= MAP_W - VIEW_W / 2)
			vx = MAP_W - VIEW_W;
		else
			vx = x - VIEW_W / 2;
		if (y < VIEW_H / 2)
			vy = 0;
		else if (y >= MAP_H - VIEW_H / 2)
			vy = MAP_H - VIEW_H;
		else
			vy = y - VIEW_H / 2;

		for (int i = 0; i < VIEW_W * VIEW_H; ++i)
		{
			//����
			bool flag = true;
			for (int j = 0; j < clients.size(); ++j)
			{
				if ((clients[j].x - vx) + (clients[j].y - vy) * VIEW_W == i)
				{
					cout << clients[j].name;
					flag = false;
					break;
				}
			}
			if (flag)
				cout << "��";
			if (i % VIEW_W == VIEW_W - 1)
				cout << endl;
		}

		//�õ�����̨�Ĵ��ھ��
		HWND hwnd = GetConsoleWindow();
		if (hwnd == GetForegroundWindow())
		{
			int x1 = x;
			int y1 = y;
			if ((::GetAsyncKeyState(VK_UP) & 1) && y > 0)
				y -= 1;
			if ((::GetAsyncKeyState(VK_DOWN) & 1) && y < MAP_H - 1)
				y += 1;
			if ((::GetAsyncKeyState(VK_LEFT) & 1) && x > 0)
				x -= 1;
			if ((::GetAsyncKeyState(VK_RIGHT) & 1) && x < MAP_W - 1)
				x += 1;
			if (x != x1 || y != y1)
			{
				_CLIENT client1;
				client1.x = x;
				client1.y = y;
				client1.lianjie1 = false;
				client1.shanchu = false;
				send(s, (char*)&client1, sizeof(client1), 0);
			}
		}
		Sleep(20);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}