#ifndef _PLANE_H_
#define _PLANE_H_
#include <windows.h>
#include <vector>

class CBullet;

class CPlane
{
	POINT m_Point;//��¼�ɻ�λ��
	int m_iHp;//�ɻ�Ѫ��
public:
	CPlane();
	virtual ~CPlane();

	//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
	virtual void Init(POINT p);

	//���÷ɻ�λ�ã���Ҫ����Ӣ��
	virtual void SetPlanePoint(POINT p);

	//�ɻ����У���Ҫ���ڵл�
	virtual bool Run(int right,int bottom,std::vector<CBullet*> vBullet);

	//����Ѫ��
	virtual void SetHP(int hp);

	//��ȡѪ��
	virtual int GetHP();

	//��ȡλ��
	virtual POINT GetPoint();

	//����
	virtual void Attack(POINT p,std::vector<CBullet*> vBullet);
}; 

#endif