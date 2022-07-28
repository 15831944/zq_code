#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

#define MAP_W 8
#define MAP_H 8
#define MAP_S (MAP_W * MAP_H)

struct POS
{
	short x : 8, y : 8;
};

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
	//�����׽���Ϊ������ģʽ
	unsigned long nonblocking = 1;
	ioctlsocket(sListen, FIONBIO, &nonblocking);

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

	cout << "�������Ѿ�������" << endl;

	SOCKET sClient;
	sockaddr_in ci;
	int ci_len = sizeof(ci);

	//��������ͻ���λ��
	POS ser_pos;
	POS cli_pos;
	ser_pos.x = 0;
	ser_pos.y = 0;

	//��ʼ����ͼ
	char map[MAP_S] = {};

	while (1)
	{
		sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
		if (INVALID_SOCKET == sClient)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				cout << "accept����";
				system("pause");
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else
		{
			if (recv(sClient, (char*)&cli_pos, sizeof(POS), 0) > 0)
				break;
			else
			{
				cout << "δ�ܳ�ʼ����ͼ�������˳���Ϸ" << endl;
				closesocket(sListen);
				closesocket(sClient);
				WSACleanup();
				system("pause");
				return;
			}
		}
	}

	if (send(sClient, (char*)&ser_pos, sizeof(POS), 0) > 0)
		;
	else
	{
		cout << "��ʼ���ͻ������ݴ��󣬼����˳���Ϸ" << endl;
		closesocket(sListen);
		closesocket(sClient);
		WSACleanup();
		system("pause");
		return;
	}

	system("cls");

	while (1)
	{
		system("cls");
		int r = recv(sClient, (char*)&cli_pos, sizeof(POS), 0);
		if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				cout << "�ͻ��˵��ߣ������˳���Ϸ" << endl;
				break;
			}
		}
		else if (r == 0)
		{
			cout << "�ͻ����˳�����Ϸ�������˳���Ϸ" << endl;
			break;
		}

		r = send(sClient, (char*)&ser_pos, sizeof(POS), 0);
		if (r == 0)
			cout << "��������ʧ�ܣ�������" << endl;

		for (int i = 0; i < MAP_S; ++i)
		{
			//������
			if (i == ser_pos.x + ser_pos.y * MAP_W)
				cout << "��";
			else if (i == cli_pos.x + cli_pos.y * MAP_W)
				cout << "��";
			else if (map[i] == 0)
				cout << "��";
			if (i % MAP_W == MAP_W - 1)
				cout << endl;
		}

		if ((GetAsyncKeyState('W') & 1) && ser_pos.y > 0)
			--ser_pos.y;
		if ((GetAsyncKeyState('S') & 1) && ser_pos.y < MAP_H - 1)
			++ser_pos.y;
		if ((GetAsyncKeyState('A') & 1) && ser_pos.x > 0)
			--ser_pos.x;
		if ((GetAsyncKeyState('D') & 1) && ser_pos.x < MAP_W - 1)
			++ser_pos.x;
	}
	closesocket(sListen);
	closesocket(sClient);
	WSACleanup();
	system("pause");
}