#ifndef _BOOM_H_
#define _BOOM_H_
#include <windows.h>
#include "GameEngine.h"
class CBoom
{
	//��ը��ľ���
	RECT m_rRect;
	//���õ�ʱ��
	int m_iTime;
public:
	CBoom(RECT r,int time);
	virtual ~CBoom();
	//���Ʊ�ը����
	virtual void Paint();
	//��ը�߼�����
	virtual bool Run();
};
#endif