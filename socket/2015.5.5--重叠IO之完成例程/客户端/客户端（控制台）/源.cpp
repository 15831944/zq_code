#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
void main()
{
	//1���������绷��
	//2�������׽���
	//3�����ݷ�����IP��ַ����ַ��Ϣ�ṹ��
	//4��ͨ���׽��ֺ͵�ַ��Ϣ�ṹ���������ӷ�����
	//5��ҵ��ѭ��
	//6���ر��׽���
	//7���ر����绷��

	 //1���������绷��
	WORD wVer = MAKEWORD(SOCK_VERH,SOCK_VERL);
    WSADATA wd;
	int err = ::WSAStartup(wVer,&wd);
	if(0 != err)
    {
       cout << "�޷���ʼ��"<<SOCK_VERH<<"."<<SOCK_VERL<<"�汾��Socket����!" << endl;
        return ;
    }
    if ( LOBYTE( wd.wVersion ) != SOCK_VERH ||
        HIBYTE( wd.wVersion ) != SOCK_VERL ) 
    {
       cout<<"�޷���ʼ��%d.%d�汾��Socket����!"<<endl;
        WSACleanup( );
        return ; 
    }

	//2�������׽���
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3�����ݷ�����IP��ַ����ַ��Ϣ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //������IP��ַ

	//4��ͨ���׽��ֺ͵�ַ��Ϣ�ṹ���������ӷ�����
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"�޷����ӷ�������";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	//5��ҵ��ѭ��
	while (1)
	{
		char buf[256];
		std::cout<<"������Ҫ���͵��ַ�����";
		std::cin>>buf;

		//�������ݵ�������
		send(
			sServer, //��Ӧ�������������׽���
			buf, //�������ݵ��ڴ��ַ
			strlen(buf) + 1, //�������ݵ��ڴ泤��
			0);

		//������͵���quit���˳�����
		if (strcmp(buf, "quit") == 0)
			break;
	}

	//6���ر��׽���
	closesocket(sServer);

	//7���ر����绷��
	WSACleanup();

	system("pause");
}