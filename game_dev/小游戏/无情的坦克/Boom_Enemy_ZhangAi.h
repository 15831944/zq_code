#ifndef _ENEMY_ZHANGAI_H_
#define _ENEMY_ZHANGAI_H_
#include "Boom.h"
class CBoom_Enemy_ZhangAi : public CBoom
{
	//��ըͼƬ����
	RECT m_rRect;
	//��ըʱ��
	int m_iTime;
public:
	CBoom_Enemy_ZhangAi(RECT r,int time);
	~CBoom_Enemy_ZhangAi();
	//��ը����ͼƬ
	void Paint();
	//��ը����
	bool Run();
};
#endif