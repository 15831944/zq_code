//��ʽ����Э�飬һ��һ���Է��Ͷ������ݣ���һ�˲�һ��һ�ο���
//����ô�����ݣ�����A��B���ӳɹ���Aһ�η�����1000���ֽڵ�B����
//��B�п���һ���ղ���1000���ֽڣ��п��������յ�200���ֽڣ���һ
//���ٵ���recv��ʱ�����ܵ�800���ֽڣ����п�����Aһ�η�����100��
//�ֽڣ�Ȼ��ܿ��ַ�����200���ֽڣ���ôB�п���һ���յ�300���ֽ�

//int send(SOCKET s, const char* buf, 100, int flags);
//���û�д���������ôsend���ر��η��͵��ֽ������������
//�п�����С������������β�len�ģ����д�������ʱ�򣬱�
//�����ķ���ֵ��SOCKET_ERROR

//int recv(SOCKET s, char* buf, int len, int flags);
//���û�д�����������ֵ���Ǳ����յ������ֽ����������ǰ
//���ӱ����ŶϿ�����ô����ֵ��0�������������򷵻�ֵ��
//SOCKET_ERROR��ע�Ȿ������len�Ǹ�֪����ϵͳ���ν���
//���ݵ����ޣ�����len��дΪ4������ʱ�Ѿ�������9���ֽ�
//����ô����Ҳֻ��õ���9���ֽ��е�ǰ4��������5���ǵ�
//�����ģ����ǿ�����һ���ٵ���recv�õ������5���ֽ�

#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET sClient = accept(sListen, (sockaddr*)&ci, &ci_len);

	char* c_name = inet_ntoa(ci.sin_addr);
	std::cout<<c_name<<"���ӵ�������"<<std::endl;

	//7��ҵ��ѭ��
	while (1)
	{
		int all_bytes;
		int r = recv(sClient, (char*)&all_bytes, 4, 0);
		if (r == 0 || r == SOCKET_ERROR)
			break;

		//�����ļ�ѭ��
		int cur_bytes = 0;
		char* p = new char[all_bytes];
		while (cur_bytes < all_bytes)
		{
			r = recv(sClient, p + cur_bytes, all_bytes - cur_bytes, 0);
			if (r == 0 || r == SOCKET_ERROR)
				exit(0);
			else
				cur_bytes += r;
		}

		FILE* pf = 0; 
		fopen_s(&pf, p, "wb");
		int fn_len = strlen(p);
		fwrite(p + fn_len + 1, all_bytes - (fn_len + 1), 1, pf);
		fclose(pf);

		delete [] p;
	}

	closesocket(sClient);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}