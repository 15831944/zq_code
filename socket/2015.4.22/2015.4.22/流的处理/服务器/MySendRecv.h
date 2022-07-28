#ifndef _MY_SEND_RECV_H_
#define _MY_SEND_RECV_H_

#include <Winsock2.h>
#include <vector>

struct _NET_EVENT //�����¼��ṹ��
{
	int type; //�¼����ͣ�0��ʾ���ӶϿ���1��ʾ�յ�����
	void* data; //���¼�����Ϊ1��ʱ�򣬱���Ա��ʾ���ݵ��׵�ַ
	int size; //���¼�����Ϊ1��ʱ�򣬱���Ա��ʾ���ݵĳ���
};

class CMySendRecv
{
	SOCKET m_Socket; //�׽���
	
	struct _SEND_DATA //�������ݽṹ��
	{
		int allsize; //���ݰ��ܴ�С
		char* data; //����
		int sendsize; //�Ѿ����͵Ĵ�С
	};
	struct _RECV_DATA //�������ݽṹ��
	{
		int allsize; //�����ܳ���
		//�����紫�����п�����������ܳ��ȶ�һ�����ղ�
		//�꣬�����ñ���Ա��ʾ������ܳ������м����ֽ�
		//��Ч��ֻ�е�����ԱΪ4��ʱ����ô������ܳ��Ȳ�
		//��������������
		int allsize_bytes; //�����ܳ��ȵ���Ч�ֽ�
		char* data; //����
		int recv_size; //�Ѿ��յ������ݳ���
	};
	std::vector<_SEND_DATA> sdlist; //���ͱ�
	_RECV_DATA recv_data; //����
	std::vector<_NET_EVENT> nelist; //�����¼���
	void _Send();
	void _Recv();
public:
	CMySendRecv(SOCKET Socket);
	void SendData(const void* Data, int Size);
	bool GetNetEvent(_NET_EVENT* pNetEvent);
	void Run();
	void Close();
};

#endif