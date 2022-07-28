#include <iostream>
#include <WinSock2.h>
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
		return;
	}
	if (LOBYTE(wd.wVersion) != SOCK_VERH ||
		HIBYTE(wd.wVersion) != SOCK_VERL)
	{
		cout << "�޷���ʼ��"<<SOCK_VERH<<"."<<SOCK_VERL<<"�汾��Socket����!" << endl;
		WSACleanup();
		return;
	}
	//�����׽���
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	cout << "�������Ѿ����������ڼ���������" << endl;

	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
	cout << inet_ntoa(ci.sin_addr) << "���ӵ�������,�׽���Ϊ��" << sClient << endl;

	while (1)
	{
		int sum;
		int r = recv(sClient, (char*)&sum, 4, 0);
		if (0 == r || SOCKET_ERROR == r)
			break;
		char* p = new char[sum];
		int bytes = 0;

		while (bytes < sum)
		{
			r = recv(sClient, p + bytes, sum - bytes, 0);
			if (0 == r || SOCKET_ERROR == r)
				exit(0);
			else
				bytes += r;
		}

		FILE* pf = NULL;
		fopen_s(&pf, p, "wb");
		int fn_len = strlen(p);
		fwrite(p + fn_len + 1, sum - (fn_len + 1), 1, pf);
		fclose(pf);
		delete[] p;
		cout << "�ѳɹ������ļ���" << endl;
	}
	closesocket(sListen);
	closesocket(sClient);
	WSACleanup();
	system("pause");
}

