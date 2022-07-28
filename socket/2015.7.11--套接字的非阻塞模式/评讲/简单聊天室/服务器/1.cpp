#include <iostream>
#define FD_SETSIZE 256
#include <Winsock2.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

struct _CLIENT
{
	SOCKET s; //�׽���
	unsigned long ip; //ip��ַ
};
std::vector<_CLIENT> clients; //�ͻ���

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//ҵ��ѭ��
	while (1)
	{
		//�����׽��ּ���
		fd_set fs;

		//����׽��ּ���
		FD_ZERO(&fs);

		//װ�ؼ����׽���
		FD_SET(s_listen, &fs);

		//װ�������׽���
		for (int i = 0; i < (int)clients.size(); ++i)
			FD_SET(clients[i].s, &fs);

		//��·����
		timeval t = {5, 500};
		select(0, &fs, 0, 0, &t);

		//������о߱��ɶ��Ե��׽���
		for (int i = 0; i < (int)fs.fd_count; ++i)
		{
			//����ǰ�߱��ɶ��Ե��׽����Ǽ����׽���
			if (fs.fd_array[i] == s_listen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(s_listen, (sockaddr*)&ci, &ci_len);
				std::cout<<inet_ntoa(ci.sin_addr)<<"���ӵ�������"<<std::endl;
				_CLIENT client = {c, ci.sin_addr.S_un.S_addr};
				clients.push_back(client);
			}
			//����ǰ�߱��ɶ��Ե��׽����������׽���
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i], buf, 256, 0);
				if (r == 0 || r == SOCKET_ERROR)
				{
					//�ڱ��в��ҷ���������׽���
					int j;
					for (j = 0; j < clients.size(); ++j)
					{
						if (fs.fd_array[i] == clients[j].s)
							break;
					}
					in_addr ia;
					ia.S_un.S_addr = clients[j].ip;
					std::cout<<inet_ntoa(ia)<<"�뿪�˷�����"<<std::endl;

					//�ر��׽���
					closesocket(clients[j].s);

					//�ӿͻ�����ɾ���׽���
					clients.erase(clients.begin() + j);
				}
				else
				{
					//����ǰ�������Ⱥ����Ϣ
					for (int j = 0; j < clients.size(); ++j)
					{
						send(clients[j].s, buf, r, 0);
					}
				}
			}
		}

		std::cout<<"��ǰ��"<<clients.size()<<"����ң�"<<std::endl;
	}

	//�ر��׽���
	closesocket(s_listen);

	//�ر����绷��
	WSACleanup();

	system("pause");
}