#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
//ʹ�ø�ģ�͵Ĳ�������:
//1).�����¼����������������¼�
//WSAEVENT WSACreateEvent( void );
//�ú����ķ���ֵΪһ���¼������������������ֹ���״̬��
//�Ѵ���(signaled)��δ����(nonsignaled)�Լ����ֹ���ģʽ��
//�˹�����(manual reset)���Զ�����(auto reset)��Ĭ��δδ���ŵĹ���״̬���˹�����ģʽ

//2).���¼��������׽��ֹ�����ͬʱע���¼���ʹ�¼�����Ĺ���״̬��δ����ת��δ�Ѵ��š� 
//int WSAEventSelect( SOCKET s,WSAEVENT hEventObject,long lNetworkEvents ); 
//sΪ�׽���
//hEventObjectΪ�ղŴ������¼�������

//3)I/O����������¼�����Ϊδ���� 
//BOOL WSAResetEvent( WSAEVENT hEvent );
//HeventΪ�¼�����
//�ɹ�����TRUE��ʧ�ܷ���FALSE

//4).�ȴ������¼��������¼�����Ĺ���״̬��
//DWORD WSAWaitForMultipleEvents( DWORD cEvents,const WSAEVENT FAR * lphEvents, BOOL fWaitAll,DWORD dwTimeout, BOOL fAlertable )
////cEventΪΪ�¼��������Ŀ�������ֵΪWSA_MAXIMUM_WAIT_EVENTS 
//lpEventΪ�¼���������ָ��
//fWaitAllָ���ȴ����ͣ�TRUE����lphEvent�����������¼�����ͬʱ���ź�ʱ���أ�
//FALSE����һ�¼����źžͷ��ء�
//dwTimeoutΪ�ȴ���ʱ�����룩
//fAlertableΪָ����������ʱ�Ƿ�ִ���������
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
	//�����׽���
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	//�׽�������
	SOCKET SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
	//�¼���������
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS NetworkEvents;
	//�ܹ����¼�����
	DWORD EventTotal = 0;
	DWORD Index ;
	//�����µ��¼�����
	WSAEVENT NewEvent = WSACreateEvent();
	//���׽���������¼�����Ԫ��һһ��Ӧ
	SocketArray[EventTotal] = sListen;
	EventArray[EventTotal++] = NewEvent;
	//�����¼����׽���
	WSAEventSelect(sListen,NewEvent,FD_ACCEPT | FD_CLOSE);
	cout<<"�������Ѿ�������"<<endl;
	while (1)
	{
		//�ȴ��������׽��ַ��ط����¼����׽���
		Index = WSAWaitForMultipleEvents(EventTotal,EventArray,FALSE,WSA_INFINITE,FALSE);
		if ( (Index == WSA_WAIT_FAILED) || (Index == WSA_WAIT_TIMEOUT) )
        {
            cout<<"WSAWaitForMultipleEvents����ʧ��!"<<endl;
            break;
        }
		//���鷢������ʲô�����¼�
		//��������������󣬸��׽��ֶ�Ӧ���¼�����Ҳ��Ӧ�Ĵ�
		//�Ѵ��ű�Ϊ��δ���ţ�Ҳ����ʹ��WSAResetEvent���
		if(0 != WSAEnumNetworkEvents(SocketArray[Index-WSA_WAIT_EVENT_0],
			EventArray[Index-WSA_WAIT_EVENT_0],&NetworkEvents))
		{
			cout<<"WSAEnumNetworkEvents����ʧ�ܣ�"<<endl;
			break;
		}
		//�����¼�Ϊ�ر�����
		if(NetworkEvents.lNetworkEvents & FD_CLOSE )
		{
			cout<<SocketArray[Index-WSA_WAIT_EVENT_0]<<"�뿪�˷�����"<<endl;
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] == 0)
			{
				//ɾ����Ӧ���׽��ֺ��¼�
				closesocket(SocketArray[Index-WSA_WAIT_EVENT_0]);
				WSACloseEvent(EventArray[Index-WSA_WAIT_EVENT_0]);
				//����ǰ��
				for(DWORD i = Index-WSA_WAIT_EVENT_0; i < EventTotal; ++i)
				{
					SocketArray[i] = SocketArray[i+1];
					EventArray[i] = EventArray[i+1];
				}
				--EventTotal;
			}
		}
		//Ϊ�����¼�
		if(NetworkEvents.lNetworkEvents & FD_ACCEPT )
		{
			if(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				//�ͻ��˵�ַ
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				//�����µ��׽��������շ�����
				SOCKET c = accept(sListen,(sockaddr*)&ci,&ci_len);
				cout<<inet_ntoa(ci.sin_addr)<<"���ӵ��˷��������׽��֣�"<<c<<endl;
				//���׽�����ӵ������У��������¼�
				EventArray[EventTotal] = WSACreateEvent();
				WSAEventSelect(c,EventArray[EventTotal],FD_WRITE | FD_READ | FD_CLOSE);
				SocketArray[EventTotal++] = c;
			}
		}
		//���¼�
		if(NetworkEvents.lNetworkEvents & FD_READ )
		{
			if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
			{
				char buf[256];
				int r = recv(SocketArray[Index-WSA_WAIT_EVENT_0],buf,256,0);
				//δ�յ�����
				if(r == 0 || r == SOCKET_ERROR)
				{
					closesocket(SocketArray[Index-WSA_WAIT_EVENT_0]);
					WSACloseEvent(EventArray[Index-WSA_WAIT_EVENT_0]);
					for(DWORD i = Index-WSA_WAIT_EVENT_0; i < EventTotal; ++i)
					{
						SocketArray[i] = SocketArray[i+1];
						EventArray[i] = EventArray[i+1];
					}
					--EventTotal;
				}
				//�յ�����
				else
					cout<<SocketArray[Index-WSA_WAIT_EVENT_0]<<"˵"<<buf<<endl;
			}
		}
	}
	system("pause");
}