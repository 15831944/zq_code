#ifndef _PLAYER_ZHANGAI_H_
#define _PLAYER_ZHANGAI_H_
#include "Boom.h"
class CBoom_Player_ZhangAi : public CBoom
{
	//��ըͼƬ����
	RECT m_rRect;
	//��ըʱ��
	int m_iTime;
public:
	CBoom_Player_ZhangAi(RECT r,int time);
	~CBoom_Player_ZhangAi();
	//��ը����ͼƬ
	void Paint();
	//��ը����
	bool Run();
};
#endif