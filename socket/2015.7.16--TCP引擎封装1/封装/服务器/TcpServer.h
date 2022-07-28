#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <Winsock2.h>
#include "MemoryPool.h"
#include "SqQueue.h"
#include "Map.h"

//�˿ں���Сֵ
#define _MIN_PORT 1025

//�����¼���Net Event��
#define _NE_CONNECTED 0 //�пͻ������ӳɹ�
#define _NE_DATA 1 //�пͻ��˷��͹�������
#define _NE_DISCONNECTED_C 2 //�ͻ��������Ͽ�
#define _NE_DISCONNECTED_S 3 //�����������Ͽ�
#define _NE_DISCONNECTED_E 4 //��Ϊ����Ͽ�
struct _NET_EVENT
{
	int type; //���ͣ�0~4��
	SOCKET s; //���������¼����׽���
	unsigned long ip; //���������¼���ip��ַ
	char* data; //����
	int len; //���ݳ���
};

class CTcpServer
{
	//���ͽṹ��
	struct _SEND_DATA
	{
		char* data; //����
		int all_size; //�����ܳ�
		int send_size; //�ѷ������ݳ���
	};

	//���սṹ��
	struct _RECV_DATA
	{
		char* data; //����
		int size_byte; //�����ܳ���Ч�ֽ���
		int all_size; //�����ܳ�
		int recv_size; //�ѽ������ݳ���
	};

	//�ͻ���
	struct _CLIENT
	{
		int state; //�ͻ���״̬
		unsigned long ip; //ip��ַ
		CSqQueue<_SEND_DATA> sd_queue; //�������ݶ���
		_RECV_DATA rd; //��������
	};

	//�����¼�����
	CSqQueue<_NET_EVENT> m_NetEvent;

	//�ͻ���
	CMap<SOCKET, _CLIENT> m_Client;

	//�ڴ��
	CMemoryPool m_MP;

	//�����׽���
	SOCKET m_Listen;

	//���������
	int m_MaxClient;

	//����������ʱ��ͼ��ʱ��
	int m_BeginKA;
	int m_IntervalKA;

	//������־
	bool m_Continue;

	//������������
	void _Accept();

	//��������
	void _Send();

	//��������
	void _Recv();

public:

	//��������
	CTcpServer();
	~CTcpServer();

	//��ʼ��
	bool Init(
		unsigned short port, //�˿ں�
		int maxclient, //���������
		int beginka, //����������ʱ��
		int intervalka); //���������ʱ��

	//����
	void Run();

	//ֹͣ
	void Stop();

	//����
	bool Continue();

	//����
	void End();

	//�õ������¼�
	bool GetNetEvent(_NET_EVENT* ne);

	//�ͷ������¼�
	void ReleaseNetEvent(_NET_EVENT* ne);

	//��������
	bool SendData(SOCKET s, const void* data, int len);

	//�Ͽ�����
	bool Disconnect(SOCKET s);
};

#endif