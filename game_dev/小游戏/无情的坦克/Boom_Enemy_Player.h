#ifndef _BOOM_ENEMY_PLAYER_H_
#define _BOOM_ENEMY_PLAYER_H_
#include "Boom.h"
class CBoom_Enemy_Player : public CBoom
{
	//��ըͼƬ����
	RECT m_rRect;
	//��ըʱ��
	int m_iTime;
public:
	CBoom_Enemy_Player(RECT r,int time);
	~CBoom_Enemy_Player();
	//��ը����ͼƬ
	void Paint();
	//��ը����
	bool Run();
};
#endif