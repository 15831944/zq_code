#include <WinSock2.h>
#include <iostream>
#include <windows.h>
using namespace std;
#define PORT 8080
//��ʽ�����׽��ֿ�
#pragma comment(lib,"WS2_32.lib")
void main()
{
	//����WSADATA�ṹ�����
	WSADATA data;
	//����汾����
	WORD w=MAKEWORD(2,0);
	//���͸��ͻ��˵��ַ���
	char sztext[]="hell,i am client";
	char RecvBuf[1024]={};
	//��ʼ���׽��ֿ�
	::WSAStartup(w,&data);
	//���������׽��ֺ������շ��׽��־��
	SOCKET s;
	//����TCP�׽���
	s=::socket(AF_INET,SOCK_STREAM,0);
	//�����׽��ֵ�ַ�ṹ
	sockaddr_in addr;
	//��ʼ����ַ�ṹ
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//��ʾ�����Ϣ
	cout<<"�������Ѿ�����\r\n";
	//����
	::connect(s,(sockaddr*)&addr,sizeof(addr));
	//?
	::send(s,sztext,sizeof(sztext),0);
	recv(s,RecvBuf,1024,0);
	printf("%s\r\n",RecvBuf);
	//�ر��׽��־��
	::closesocket(s);
	::WSACleanup();
	if(getchar())
		return;
	else
		Sleep(100);
}
