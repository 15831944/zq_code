#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888

SOCKET sServer;
int sen_file()
{
	//�õ��ļ���
	cout << "������Ҫ���͵��ļ�����";
	char fn[256];
	cin >> fn;

	//���ļ�
	FILE *pf = NULL;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return -1;

	//�õ��ļ�������
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* p = new char[strlen(fn) + 1 + fs];
	fread(p + strlen(fn) + 1, 1, fs, pf);
	memcpy(p, fn, strlen(fn) + 1);
	fclose(pf);

	//�õ�Ҫ���͵����ֽ���
	int all_bytes = strlen(fn) + 1 + fs;
	if (SOCKET_ERROR == send(sServer, (char*)&all_bytes, 4, 0))
		return 0;

	//�������ļ��ܴ�С�󣬿�ʼ��������
	int cur_bytes = 0;
	while (cur_bytes < all_bytes)
	{
		int r = send(sServer, p + cur_bytes, all_bytes - cur_bytes, 0);
		if (SOCKET_ERROR == r)
			return 0;
		else
			cur_bytes += r;
	}
	delete[] p;
	return 1;
}
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
		cout << "�޷���ʼ��" << SOCK_VERH << "." << SOCK_VERL << "�汾��Socket����!" << endl;
		WSACleanup();
		return;
	}

	//2�������׽���
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3�����ݷ�����IP��ַ����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //������IP��ַ

	//4��ͨ���׽��ֺ͵�ַ��Ϣ�ṹ���������ӷ�����
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout << "�޷����ӷ�������";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};
	while (1)
	{
		system("cls");
		cout << "<���ļ�����>"<<endl;
		cout << "1> ����"<<endl;
		cout << "2> �˳�"<<endl;
		int sel;
		cin >> sel;
		if (sel == 2)
			break;
		else if (sel == 1)
		{
			int r = sen_file();
			if (-1 == r)
			{
				cout << "�޷���ָ���ļ���";
				break;
			}
			else if (0 == r)
			{
				cout << "�ļ�����ʧ�ܣ�";
				break;
			}
			else if (1 == r)
			{
				cout << "�ļ����ͳɹ���" << endl;
				system("pause");
			}
		}		
	}
	closesocket(sServer);
	WSACleanup();
	system("pause");
}