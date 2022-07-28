#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <Winsock2.h>
#include "MemoryPool.h"
#include "SqQueue.h"
#include "Map.h"

//�˿ں���Сֵ
#define _MIN_PORT 1025

//�����������¼���Server Net Event��
#define _SNE_CONNECTED 0 //�пͻ������ӳɹ�
#define _SNE_DATA 1 //�пͻ��˷��͹�������
#define _SNE_DISCONNECTED_C 2 //�ͻ��������Ͽ�
#define _SNE_DISCONNECTED_S 3 //�����������Ͽ�
#define _SNE_DISCONNECTED_E 4 //��Ϊ����Ͽ�
struct _SNET_EVENT
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
		int len_valid_bytes; //�����ܳ���Ч�ֽ���
		int all_len; //�����ܳ�
		int recv_len; //�ѽ������ݳ���

		//�������
		void Clear()
		{
			data = 0;
			len_valid_bytes = 0;
			all_len = 0;
			recv_len = 0;
		}
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
	CSqQueue<_SNET_EVENT> m_SNetEvent;

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

	//���������б�־
	bool m_Continue;

	//������������
	bool _Accept();

	//��������
	void _Send();

	//��������
	void _Recv();

	//���յ�����ҵ�����
	void _RecvClient(char* buf, int r, SOCKET s, _CLIENT* c);

	//�ر�ָ�����
	void _CloseClient(SOCKET s, _CLIENT* c, int t);

public:

	//��������
	CTcpServer();
	~CTcpServer();

	//��ʼ��
	bool Init(
		unsigned short port, //�˿ں�
		int maxclient, //���������
		int beginka, //����������ʱ�䣨�룩
		int intervalka); //���������ʱ�䣨�룩

	//����
	void Run();

	//ֹͣ
	void Stop();

	//����
	bool Continue();

	//����
	void End();

	//�õ������¼�
	bool GetNetEvent(_SNET_EVENT* ne);

	//�ͷ������¼�
	void ReleaseNetEvent(_SNET_EVENT* ne);

	//��������
	bool SendData(SOCKET s, const void* data, int len);

	//�Ͽ�����
	bool Disconnect(SOCKET s);

	//����ip��ַת���ַ���ip��ַ����Ϊ��������������κ�
	//��Ա���������Ա����Ϻͱ�������޹أ���������Ϊ��̬��
	static char* ulong_str(unsigned long ip, char* buf);
};

#endif