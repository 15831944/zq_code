#ifndef _BULLET_BAIXIAOGUI_H_
#define _BULLET_BAIXIAOGUI_H_
#include "Bullet.h"
class CBullet_BaiXiaoGui : public CBullet
{	
	//�ӵ�λ�ã������ӵ����ͣ�����
	POINT m_pBulletPoint;
	char m_cDir;
	char m_cBulletType;
	int m_iAttack;
public:
	CBullet_BaiXiaoGui(POINT p,char dir,int att,char type);
	~CBullet_BaiXiaoGui();
	//��ȡ�ӵ�λ��
	POINT GetBulletPoint();
	//�ӵ�����
	bool BulletRun(int bianjie_R,int bianjie_D);
	//��ȡ����
	int GetAttack();
};
#endif