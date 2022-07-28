#include <iostream>
#define FD_SETSIZE 256
#include <Winsock2.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

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

	//ҵ��ѭ��
	while (1)
	{
		fd_set fs;
		FD_ZERO(&fs); //����׽��ּ���
		FD_SET(sListen, &fs); //�������׽���װ�뵽�׽��ּ�����
		for (int i = 0; i < client.size(); ++i) //���ͻ��׽���װ�뵽�׽��ּ�����
			FD_SET(client[i], &fs);

		timeval t = {2, 500};
		select(0, &fs, 0, 0, &t);

		//ѭ����ǰ���������¼����׽���
		for (int i = 0; i < fs.fd_count; ++i)
		{
			//����ǰ���������¼����׽�����
			//�����׽��֣���ô������������
			//����
			if (fs.fd_array[i] == sListen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(sListen, (sockaddr*)&ci, &ci_len);
				std::cout<<inet_ntoa(ci.sin_addr)<<"���ӵ����������׽���Ϊ"<<c<<std::endl;
				client.push_back(c);
			}
			//����ǰ���������¼����׽��ֲ���
			//�����׽��֣���ô�����пͻ��˷�
			//����������
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i], buf, 256, 0);
				if (r == 0 || r == SOCKET_ERROR)
				{
					std::cout<<fs.fd_array[i]<<"�뿪��������"<<std::endl;
					for (int j = 0; j < client.size(); ++j)
					{
						if (fs.fd_array[i] == client[j])
						{
							client.erase(client.begin() + j);
							break;
						}
					}
					closesocket(fs.fd_array[i]);
				}
				else
				{
					for (int j = 0; j < client.size(); ++j)
						send(client[j], buf, strlen(buf) + 1, 0);
				}
			}
		}
	}

	for (int i = 0; i < client.size(); ++i)
		closesocket(client[i]);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}