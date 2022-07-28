#include "Bullet.h"

CBullet :: CBullet()
{
}
CBullet ::	~CBullet()
{
}
//����ӵ��������˵Ĺ�����
int CBullet :: GetAttack()
{
	return this->m_iAttack;
}
//����ӵ���λ��
POINT CBullet :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//�ӵ�����
bool CBullet :: BulletRun(int bianjie_R,int bianjie_D)
{
	if(this->m_cDir == _DIR_UP_	)
		this->m_pBulletPoint.y -= BULLET_SPEED ;
	if(this->m_cDir == _DIR_DOWN_	)
		this->m_pBulletPoint.y += BULLET_SPEED ;
	if(this->m_cDir == _DIR_LEFT_	)
		this->m_pBulletPoint.x -= BULLET_SPEED ;
	if(this->m_cDir == _DIR_RIGHT_	)
		this->m_pBulletPoint.x += BULLET_SPEED ;
	if(this->m_pBulletPoint.x >bianjie_R || this->m_pBulletPoint.x <0
		|| this->m_pBulletPoint.y <80 || this->m_pBulletPoint.y > bianjie_D)
		return false;
	return true;
}
