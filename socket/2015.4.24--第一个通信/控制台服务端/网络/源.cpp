#include <WinSock2.h>
#include <iostream>
#include <windows.h>
#define _PORT_ 8500
using namespace std;
//��ʽ�����׽��ֿ�
#pragma comment(lib,"WS2_32.lib")
void main()
{
	//����WSADATA�ṹ�����
	WSADATA data;
	//����汾����
	WORD w=MAKEWORD(2,0);
	//���͸��ͻ��˵��ַ���
	char sztext[256]={};
	//��ʼ���׽��ֿ�
	::WSAStartup(w,&data);
	//���������׽��ֺ������շ��׽��־��
	SOCKET s,s1;
	//����TCP�׽���
	s=::socket(AF_INET,SOCK_STREAM,0);
	//�����׽��ֵ�ַ�ṹ
	sockaddr_in addr,addr2;
	//��ȡ�׽��ֵ�ַ�ṹ��С
	int n=sizeof(addr2);
	//��ʼ����ַ�ṹ
	addr.sin_family=AF_INET;
	addr.sin_port=htons( _PORT_);
	addr.sin_addr.S_un.S_addr=INADDR_ANY;
	//���׽���
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	//�����׽���
	::listen(s,5);
	//��ʾ�����Ϣ
	cout<<"�������Ѿ�����\r\n";
	cout<<"���ڵȴ��ͻ�������"<<endl;
	while(1)
	{
		//������������
		s1=::accept(s,(sockaddr*)&addr2,&n);
		if(s1!=NULL)
		{
			printf("%s�Ѿ�������\r\n",inet_ntoa(addr2.sin_addr));
			while(1)
			{
				char rec[256]={};
				recv(s1,rec,256,0);
				cout<<"�ͻ���˵��"<<rec<<endl;
				//��ͻ��˷��ͻ�ӭ��Ϣ
				cout<<"������Ҫ���͵�����:"<<endl<<"������˵��";
				cin>>sztext;
				::send(s1,sztext,sizeof(sztext),0);
			}
		}
		//�ر��׽��־��
		::closesocket(s);
		::closesocket(s1);
		//�ͷ��׽��ֿ�
		::WSACleanup();
		if(getchar())
		{
			return;
		}
		else
		{
			Sleep(100);
		}
	}
}