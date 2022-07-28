#include "Player1Bullet.h"
//����
CPlayer1Bullet :: CPlayer1Bullet(POINT p,char dir,int att,char type)
	:
//λ�ã����򣬹���������
	m_pBulletPoint(p),
	m_cDir(dir),
	m_iAttack(att),
	m_cBulletType(type)
{
}
CPlayer1Bullet :: 	~CPlayer1Bullet()
{
}
//����ӵ�λ��
POINT CPlayer1Bullet :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//��ȡ�ӵ�����
int CPlayer1Bullet :: GetAttack()
{
	return this->m_iAttack;
}
//�ӵ����У������߽緵��FALSE
bool CPlayer1Bullet :: BulletRun(int bianjie_R,int bianjie_D)
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
