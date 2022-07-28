#ifndef _NET_WORK_H_
#define _NET_WORK_H_

#include <Winsock2.h>
#include <vector>

//���ṹ����ʹ��CNetWork����˻��õ��ģ�����д������
struct _RECV_DATA
{
	char* data;
	int len;
};

class CNetWork
{
	SOCKET m_socket;

	//���ͽṹ��
	struct SD
	{
		char* data; //Ҫ���͵�����
		int all_len; //Ҫ�������ݵ��ܳ���
		int send_len; //�Ѿ��������ݵĳ���
	};
	std::vector<SD> sd_list; //���ͱ�

	//���սṹ��
	struct RD
	{
		int len_valid_bytes; //������Ч�ֽڣ����뵽4��ô���Ȳ��������ϣ�
		int all_len; //Ҫ�������ݵ��ܳ���
		char* data; //Ҫ���յ�����
		int recv_len; //�Ѿ��������ݵĳ���
	};
	RD rd; //����
	std::vector<_RECV_DATA> rd_list; //�������յ������ݱ�

	//�����������ͷ����棬��֮����ͷ��ؼ�
	bool _SendData();
	bool _RecvData();

public:

	//����
	CNetWork(SOCKET s);

	//��������
	void SendData(const void* data, int len);

	//�������ݡ��ͷ�����
	bool GetRecvDate(_RECV_DATA* recv_data);
	void ReleaseRecvData(_RECV_DATA* recv_data);

	//����
	bool Run();
};

#endif

//main()
//{
//	while (1)
//	{
//		//��������
//
//		//������
//		_RECV_DATA rd;
//		while (CNetWork.GetRecvDate(&rd))
//		{
//			//�������ݰ�
//
//			CNetWork.ReleaseRecvData(&rd);
//			free(&rd);
//		}
//	}
//}