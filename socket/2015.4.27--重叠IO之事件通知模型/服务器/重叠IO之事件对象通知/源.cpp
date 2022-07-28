#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
#define DATA_BUSIZE 5096

void main()
{
	WORD wVer = MAKEWORD(SOCK_VERH,SOCK_VERL);
    WSADATA wd;
    int err = ::WSAStartup(wVer,&wd);
    if(0 != err)
    {
       cout<<"�޷���ʼ��Socket2ϵͳ����!"<<endl;
        return ;
    }
    if ( LOBYTE( wd.wVersion ) != SOCK_VERH ||
        HIBYTE( wd.wVersion ) != SOCK_VERL ) 
    {
       cout << "�޷���ʼ��"<<SOCK_VERH<<"."<<SOCK_VERL<<"�汾��Socket����!" << endl;
        WSACleanup( );
        return ; 
    }
	//�������ṹ
	WSABUF DataBuf;
	char buffer[DATA_BUSIZE] = {};
	DataBuf.buf = buffer;
	DataBuf.len = DATA_BUSIZE;
	//�ص��ṹ
	WSAOVERLAPPED AcceptOverlapped;
	//����
	ZeroMemory(&AcceptOverlapped,sizeof(AcceptOverlapped));
	//�¼�����
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS] = {};
	//�¼�����
	DWORD EventTotal = 0;
	//�����¼�
	EventArray[EventTotal] = WSACreateEvent();
	AcceptOverlapped.hEvent = EventArray[EventTotal];
	EventTotal ++;
	//�յ����ַ�������
	DWORD RecvBytes = 0;
	DWORD BytesTransferred = 0;
	//WSARecv�еĲ���
	DWORD Flags = 0;
	SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//����������ַ�ṹ��
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen,(sockaddr*)&si,sizeof(si));
	listen(sListen,5);
	cout<<"�������Ѿ���������"<<endl;
	//�ͻ��˵�ַ��Ϣ
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET AcceptSocket = accept(sListen,(sockaddr*)&ci,&ci_len);
	cout<<inet_ntoa(ci.sin_addr)<<"���ӵ�������,�׽���Ϊ��"<<AcceptSocket<<endl;
	while (1)
	{
		//��������
		if(WSARecv(AcceptSocket,&DataBuf,1,&RecvBytes,&Flags,&AcceptOverlapped,NULL)
			== SOCKET_ERROR)
		{
			//����WSA_IO_PENDING ��������������ǵĻ��ͳ�������
			//ֻ�ܹر��׽�����
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				closesocket(AcceptSocket);
				WSACloseEvent(EventArray[EventTotal]);
			}
		}
		//�¼�����
		DWORD Index = WSAWaitForMultipleEvents(EventTotal,EventArray,FALSE,WSA_INFINITE,FALSE);
		//�����¼��ź�
		WSAResetEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
		//����ص��ṹ�Ľ��
		WSAGetOverlappedResult(AcceptSocket,&AcceptOverlapped,&BytesTransferred,FALSE,&Flags);
		//�յ�������Ϊ0������ͻ����Ѿ��˳��˷�����
		if(BytesTransferred == 0)
		{
			cout<<AcceptSocket<<"�˳��˷�����!"<<endl;
			closesocket(AcceptSocket);
			WSACloseEvent(EventArray[EventTotal]);
			break;
		}
		//��������
		if(WSASend(AcceptSocket,&DataBuf,1,&RecvBytes,Flags,&AcceptOverlapped,NULL)
			== SOCKET_ERROR)
			cout<<"���ͳ���"<<endl;
		cout<<AcceptSocket<<"˵:"<<DataBuf.buf<<endl;
	}
	closesocket(sListen);
	WSACleanup();
	system("pause");
}