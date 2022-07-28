#ifndef _EMENYPLANE_H_
#define _EMENYPLANE_H_

#include "Plane.h"

class CBullet;

class CEmenyPlane : public CPlane
{
	POINT m_Point;//��¼�ɻ�λ��
	int m_iHp;//�ɻ�Ѫ��
	int m_iDirect;//��¼�ɻ�����0 ���£�1 ����2 ������
	int m_iTimeAtt;//�����ӵ���ʱ�������������Ӧ���������.
public:
	CEmenyPlane();
	~CEmenyPlane();

	//��ʼ����������ʼ���ɻ���λ�ã�Ѫ��
	void Init(POINT p);

	//�ɻ����У���Ҫ���ڵл�
	bool Run(int right,int bottom,std::vector<CBullet*>& vBullet);

	//����Ѫ��
	void SetHP(int hp);

	//��ȡѪ��
	int GetHP();

	//��ȡλ��
	POINT GetPoint();

	//����
	void Attack(POINT p,std::vector<CBullet*>& vBullet);
}; 

#endif