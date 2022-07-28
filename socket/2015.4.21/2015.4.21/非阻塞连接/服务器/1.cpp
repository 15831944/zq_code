#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	//�õ�����̨���ھ��
	HWND hwnd = GetConsoleWindow();

	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//�����׽���Ϊ������������ʽ��������ü����׽���Ϊ
	//�������ģ���ô��������׽��ֵõ��������׽��ֶ���
	//���Զ�����Ϊ�������׽���
	unsigned long nonblocking = 1;
	ioctlsocket(sListen, FIONBIO, &nonblocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen, (sockaddr*)&si, sizeof(si));
	listen(sListen, 8);
	sockaddr_in ci;
	int ci_len = sizeof(ci);

	SOCKET sClient;
	while (1)
	{
		sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
		if (INVALID_SOCKET == sClient)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				std::cout<<"��ǰ��������"<<std::endl;
			else
			{
				std::cout<<"��ĳ����ˣ�";
				system("pause");
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else
			break;
	}

	system("cls");

	while (1)
	{
		//GetForegroundWindow���Եõ���ǰ����ϵͳ��λ��
		//���Ĵ��ڣ����������жϱ�����̨�ǲ�������
		//����
		if (GetForegroundWindow() == hwnd)
		{
			for (char i = 'A'; i <= 'Z'; ++i)
			{
				if (GetAsyncKeyState(i) & 0x8000)
					send(sClient, &i, 1, 0);
			}
		}

		char buf[256];
		int r = recv(sClient, buf, 256, 0);
		if (r > 0)
		{
			for (int i = 0; i < r; ++i)
				std::cout<<buf[i];
		}
		else if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				std::cout<<"��ĳ����ˣ�";
				system("pause");
				closesocket(sClient);
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else if (r == 0)
			break;

		Sleep(20);
	}

	closesocket(sClient);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}