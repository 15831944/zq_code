#ifndef _QIZI_H_
#define _QIZI_H_
//���ӵĸ��࣬���е����Ӷ��̳�������ࡣ��ʵ���䱾����߼�
class CQiZi
{
	int m_iQiZiX;//���ӵ�X����
	int m_iQiZiY;//���ӵ�Y����
public:
	//���ӵ��߼�
	virtual bool Logic(int x,int y);
};

#endif