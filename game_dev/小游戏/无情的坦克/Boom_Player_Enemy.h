#ifndef _BOOM_PLAYER_ENEMY_H_
#define _BOOM_PLAYER_ENEMY_H_
#include "Boom.h"
class CBoom_Player_Enemy : public CBoom
{
	//��ըͼƬ����
	RECT m_rRect;
	//��ըʱ��
	int m_iTime;
public:
	CBoom_Player_Enemy(RECT r,int time);
	~CBoom_Player_Enemy();
	//��ը����ͼƬ
	void Paint();
	//��ը����
	bool Run();
};
#endif