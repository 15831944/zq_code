#ifndef _WZQ_H_
#define _WZQ_H_

#define _ER -1
#define _KZ 0
#define _HZ 1
#define _BZ 2

#define _QPW 20
#define _QPH 20

#define _QPS (_QPW * _QPH)


class CWZQ
{
	char qp[_QPS];//����
	char c;//��ǰ���ӵ���ɫ

	int _ZX(int x,int y);
	
public:
	void Init();

	//�����ж�
	//_ER : ���ӳ�������ڸ�λ������
	//_KZ : û��ʤ��
	//_HZ : ����ʤ��
	//_BZ : ����ʤ��
	int LuoZi(int x,int y);

	//��ȡ���̵�����(������ʾ)
	const char* getqp();

	//�õ���ǰ���ӵ���ɫ
	char getc();
};

#endif