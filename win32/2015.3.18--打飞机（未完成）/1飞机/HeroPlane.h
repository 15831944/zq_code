#ifndef _HEROPLANE_H_
#define _HEROPLANE_H_

#include "Plane.h"

class CBullet;

class CHeroPlane : public CPlane
{
	POINT m_Point;//��¼�ɻ�λ��
	int m_iHp;//�ɻ�Ѫ��
public:
	CHeroPlane();
	~CHeroPlane();

	//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
	void Init(POINT p);

	//���÷ɻ�λ�ã���Ҫ����Ӣ��
	void SetPlanePoint(POINT p);

	//����Ѫ��
	void SetHP(int hp);

	//��ȡѪ��
	int GetHP();

	//��ȡλ��
	POINT GetPoint();

	//����
	void Attack(POINT p,std::vector<CBullet*> vBullet);
}; 

#endif