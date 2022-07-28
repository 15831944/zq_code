#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
#define DATA_BUSIZE 5096

//�Զ����ص��ṹ
struct MyOverlapped
{
	WSAOVERLAPPED m_wsaol;			//�ص��ṹ
	long		  m_lNetworkEvents; //�¼����ͣ�FD|READ / FD_WRITE)
	SOCKET        m_socket;			//socket���
	void*         m_pbuf;			//Ͷ�ݲ���ʱ�Ļ���
	size_t		  m_szBufLen;		//���峤��
	DWORD	      m_dwTrasBytes;	//WSARecv��WSASend׼���Ĳ���
	DWORD		  m_dwFlags;		//WSARecv��WSASend׼���Ĳ���
};
//������̵�Ͷ�ݺ���
void CALLBACK CompletionRoutine(
								DWORD dwError,//��־����Ͷ�ݵ��ص�����������WSARecv,��ɵ�״̬��ʲô
								DWORD cbTransfered,//ָ�������ص������ڼ䣬ʵ�ʴ�����ֽ����Ƕ��
								LPWSAOVERLAPPED lpOverlapped,//ָ�����ݵ������io�����ڵ�һ���ص��ṹ
								DWORD dwFlags);//���ز�������ʱ�����õı�־��һ��û�ã�
void main()
{
	//�汾�뻷�����
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
        cout<<"�޷���ʼ���汾��Socket����!"<<endl;
        WSACleanup( );
        return ; 
    }
	//��ʼ���������׽������ַ
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM ,IPPROTO_TCP);
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(_PORT);
	//���׽������ַ
	bind(ListenSocket,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr));
	//����
	listen(ListenSocket,5);
	cout<<"���ڵȴ��ͻ��˵Ľ��롣��"<<endl;
	//�ͻ����׽������ַ
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKET AcceptSocket = accept(ListenSocket,(SOCKADDR*)&ClientAddr,&len);
	cout<<inet_ntoa(ClientAddr.sin_addr)<<"�Ѿ����ӽ����ˣ��׽���Ϊ��"<<AcceptSocket<<endl;
	//׼�����ص��ṹ�뻺����
	WSABUF DataBuf = {};
	char buffer[DATA_BUSIZE] = {};
	DataBuf.buf = buffer;
	DataBuf.len = DATA_BUSIZE;
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS]={};
	//��������Ҫ��Ϣͨ����չOVERLAPPED�Ľṹ�����ص�������ȥ
	MyOverlapped AcceptOverlapped = {};
	AcceptOverlapped.m_socket = AcceptSocket;
	AcceptOverlapped.m_pbuf = DataBuf.buf;
	AcceptOverlapped.m_lNetworkEvents = FD_READ;
	AcceptOverlapped.m_szBufLen = DATA_BUSIZE;
	//���WSARecv����
	do{
		if(WSARecv(AcceptSocket,&DataBuf,1,&AcceptOverlapped.m_dwTrasBytes,&AcceptOverlapped.m_dwFlags,
				(WSAOVERLAPPED*)&AcceptOverlapped.m_wsaol,CompletionRoutine) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				system("pause");
				break;
			}
		}
		cout<<"�ص�������ɡ���"<<endl;
	}while(WAIT_IO_COMPLETION == SleepEx(INFINITE,TRUE));
	if(INVALID_SOCKET != ListenSocket)
		closesocket(ListenSocket);
	WSACleanup();
}
//���������Ҫ�ĺ���
void CALLBACK CompletionRoutine(
								DWORD dwError,//��־����Ͷ�ݵ��ص�����������WSARecv,��ɵ�״̬��ʲô
								DWORD cbTransfered,//ָ�������ص������ڼ䣬ʵ�ʴ�����ֽ����Ƕ��
								LPWSAOVERLAPPED lpOverlapped,//ָ�����ݵ������io�����ڵ�һ���ص��ṹ
								DWORD dwFlags)//���ز�������ʱ�����õı�־��һ��û�ã�
{
	//�õ���ȷ�Ľṹ��ָ��
	MyOverlapped *pMy01 =CONTAINING_RECORD(lpOverlapped,MyOverlapped,m_wsaol);
	//�Ͽ�������
	if(0 != dwError || 0 == cbTransfered)
	{
		cout<<pMy01->m_socket<<"�˳������ӣ�"<<endl;
		closesocket(pMy01->m_socket);
		return ;
	}
	if(pMy01->m_lNetworkEvents == FD_READ)
	{
		cout<<pMy01->m_socket<<"˵��"<<(char*)pMy01->m_pbuf<<endl;
	}
}
