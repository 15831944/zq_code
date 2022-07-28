#include "Bullet_BaiXiaoHua.h"
//����
CBullet_BaiXiaoHua :: CBullet_BaiXiaoHua(POINT p,char dir,int att,char type)
	:
	m_pBulletPoint(p),
	m_cDir(dir),
	m_iAttack(att),
	m_cBulletType(type)
{
}
CBullet_BaiXiaoHua ::	~CBullet_BaiXiaoHua()
{

}
//��ȡ����
int CBullet_BaiXiaoHua :: GetAttack()
{
	return this->m_iAttack;
}
//��ȡ�ӵ�λ��
POINT CBullet_BaiXiaoHua :: GetBulletPoint()
{
	return this->m_pBulletPoint;
}
//�ӵ����У������߽緵��FALSE
bool CBullet_BaiXiaoHua :: BulletRun(int bianjie_R,int bianjie_D)
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
