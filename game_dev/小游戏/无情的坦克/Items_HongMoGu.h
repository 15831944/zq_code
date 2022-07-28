#ifndef _ITEMS_HONGMOGU_H_
#define _ITEMS_HONGMOGU_H_
#include "Items.h"
class CHongMoGU : public CItems
{
	//��������
	std::string m_sName;
	//������������
	int m_iDefence;
	//������������
	int m_iAttack;
	//��������Ѫ��
	int m_iHp;
	//�����Ƿ����
	bool m_bDisapper;
	//����ͼƬ����
	RECT m_rRect;
public:
	CHongMoGU(std::string s,int de,int att,int hp,bool apper);
	~CHongMoGU();
	//��õ��ߵķ�����
	int GetDefence();
	//��õ��ߵĹ�����
	int GetAtt();
	//��õ��ߵ�Ѫ��
	int GetHp();
	//���õ����Ƿ����
	void SetApper(bool apper);
	//��õ��ߵ�ǰ�Ƿ���ֵĲ���ֵ
	bool GetApper();
	//���õ���ͼƬ�ľ���
	void SetRect(RECT r);
	//��õ���ͼƬ�ľ���
	RECT GetRect();
	//��õ��ߵ�����
	std::string  GetName();
};
#endif