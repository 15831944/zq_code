#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
//������Ĭ������£�recv������accept����������δ����֮ǰ�ͻ�һֱ�ȴ�
//���������������̣߳������ͻᵼ�£�
//1��.�޷�ͬһʱ��Ƚ��������ֽ�������
//2��.�޷�ͬһʱ��ȴ����˷�������
//��ô�������2���������������취��
//����취һ��
//ʹ�ö��̣߳����߳�����accept�����ͻ��˵����ӣ�Ȼ����һ���߳�
//�������ӽ����Ŀͻ��ˣ�����������߳̾�ר������Ϊ�ͻ��˷���
//���������и��׶˾��ǣ������1000���ͻ������ӽ������ǾͿ�����1000���̣߳�
//�����������ľͷǳ���
//����취����ʹ�ö�·���ú���
//int select(
//			int nfds//���ã�������Ϊ�˺�Unix�����select�β���ͬ
//			fd_set *readfds//�����ɶ��Ե��׽��ּ���
//			fd_set *writefds//������д�Ե��׽��ּ���
//			fd_set *exceptfds//����ⷢ���쳣���׽��ּ���
//			const struct timeval* timeout//�ȴ�ʱ�䣬Ϊ0Ϊ���޵ȴ�)
//typedef struct fd_set//�׽��ּ��Ͻṹ��
//{
//		u_int fd_count;//��������Ч�׽��ֵ�����
//		SOCKET fd_array[FD_SETSIZE];//�׽������飬����FD_SIZE
//									����������������ȷ������ֵ��С
//}fd_set;
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

	//�ͻ��׽���
	std::vector<SOCKET> client;
	cout<<"�������Ѿ�������"<<endl;
	while (1)
	{
		fd_set fs;
		//����׽��ּ���
		FD_ZERO(&fs);
		//�Ѽ����׽���װ�뼯����
		FD_SET(sListen,&fs);
		//�ѿͻ����׽���װ�뵽������
		for(int i = 0; i < client.size(); ++i)
			FD_SET(client.at(i),&fs);
		timeval t = {2.0};
		select(0,&fs,0,0,&t);
		//ѭ����ǰ���������¼����׽���
		for(int i = 0; i < fs.fd_count; ++i)
		{
			//����ǰ�����¼����׽����Ǽ����׽���
			//��˵���пͻ������ӽ�����
			if(fs.fd_array[i] == sListen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(sListen,(sockaddr*)&ci,&ci_len);
				cout<<inet_ntoa(ci.sin_addr)<<"���ӵ�������,�׽���Ϊ��"<<c<<endl;
				client.push_back(c);
			}
			//����ǰ���Ǽ����׽��ַ��������¼���
			//�Ǿ��ǿͻ��˷���������
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i],buf,256,0);
				if( r == 0 || r == SOCKET_ERROR)
				{
					cout<<fs.fd_array[i]<<"�뿪�˷�����"<<endl;
					for(int j = 0; j < client.size(); ++j)
					{
						if(fs.fd_array[i] == client.at(j))
						{
							client.erase(client.begin() + j);
							break;
						}
					}
				}
				else
					cout<<fs.fd_array[i]<<"˵:"<<buf<<endl;
			}
		}
	}
	for(int i = 0; i < client.size(); ++i)
		closesocket(client[i]);
	closesocket(sListen);
	WSACleanup();
	system("pause");
}