#ifndef _BULLET_BAIXIAOHUA_H_
#define _BULLET_BAIXIAOHUA_H_
#include "Bullet.h"
class CBullet_BaiXiaoHua : public CBullet
{
	//�ӵ�λ�ã������ӵ����ͣ�����
	POINT m_pBulletPoint;
	char m_cDir;
	char m_cBulletType;
	int m_iAttack;
public:
	CBullet_BaiXiaoHua(POINT p,char dir,int att,char type);
	~CBullet_BaiXiaoHua();
	//��ȡ�ӵ�λ��
	POINT GetBulletPoint();
	//�ӵ�����
	bool BulletRun(int bianjie_R,int bianjie_D);
	//��ȡ����
	int GetAttack();
};
#endif