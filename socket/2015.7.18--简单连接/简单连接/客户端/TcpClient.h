#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <Winsock2.h>
#include "MemoryPool.h"
#include "SqQueue.h"

//�˿ں���Сֵ
#define _MIN_PORT 1025

//�ͻ��������¼���Client Net Event��
#define _CNE_CONNECT_OK 0 //���ӷ������ɹ�
#define _CNE_CONNECT_FAIL 1 //���ӷ�����ʧ��
#define _CNE_DATA 2 //���������͹�������
#define _CNE_DISCONNECTED_C 3 //�ͻ��������Ͽ�
#define _CNE_DISCONNECTED_S 4 //�����������Ͽ�
#define _CNE_DISCONNECTED_E 5 //��Ϊ����Ͽ�
struct _CNET_EVENT
{
	int type; //���ͣ�0~4��
	char* data; //����
	int len; //���ݳ���
};

class CTcpClient
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

	SOCKET m_Socket; //�׽���
	int m_State; //״̬
	CSqQueue<_SEND_DATA> m_SDQueue; //�������ݶ���
	_RECV_DATA m_RD; //��������

	//�����¼�����
	CSqQueue<_CNET_EVENT> m_CNetEvent;

	//�ڴ��
	CMemoryPool m_MP;

	//����������ʱ��ͼ��ʱ��
	int m_BeginKA;
	int m_IntervalKA;

	//�ȴ�����ʱ��
	int m_Wait;
	
	//��ǰʱ��
	int m_ConnectTime;

	//�ر��׽��ּ������������Դ
	void _CloseSocket(int t);

	//��������
	void _Send();

	//��������
	void _Recv();

	//������յ�������
	void _RecvData(char* buf, int r);

public:

	//��������
	CTcpClient();
	~CTcpClient();

	//IP��ַ����
	bool ConnectIP(
		const char* ip, //������ip��ַ
		unsigned short port, //�������˿ں�
		int wait, //���ӵȴ�ʱ��
		int beginka, //����������ʱ�䣨�룩
		int intervalka); //���������ʱ�䣨�룩

	//��������
	//������һ��internet����ķ���һ����˵��ר��
	//��������������DNS�����������������ν������ʵ
	//���Ƕ�ip��ַ��һ���������ֶΣ���һ���Ƚ�����
	//��������������������Լ����ip��ַ���ڸ���
	//�����������ж�����Ӧ��������ͨ������������
	//ip��ַ�����ھ���ĳ�����ֻ��Ҫ������ת��Ϊip
	//ip��ַ�������Ӽ���
	bool ConnectName(
		const char* name, //����������
		unsigned short port, //�������˿ں�
		int wait, //���ӵȴ�ʱ��
		int beginka, //����������ʱ�䣨�룩
		int intervalka); //���������ʱ�䣨�룩

	//�õ������¼�
	bool GetNetEvent(_CNET_EVENT* ne);

	//�ͷ������¼�
	void ReleaseNetEvent(_CNET_EVENT* ne);

	//��������
	bool SendData(const void* data, int len);

	//�Ͽ�����
	bool Disconnect();

	//����
	void Run();
};

#endif