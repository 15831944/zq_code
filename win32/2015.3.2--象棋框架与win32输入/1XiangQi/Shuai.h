#ifndef _SHUAI_H_
#define _SHUAI_H_
#include "QiZi.h"

//˧
class CShuai : public CQiZi
{
	int m_iQiZiX;//���ӵ�X����
	int m_iQiZiY;//���ӵ�Y����
public:
	//���ӵ��߼�
	bool Logic(int x,int y);
};

#endif