#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <vector>
#include <string>
#include <windows.h>
class CItems
{
	//��������
	std::string m_sName;
	//���߷�����
	int m_iDefence;
	//������
	int m_iAttack;
	//Ѫ��
	int m_iHp;
	//�Ƿ����
	bool m_bDisapper;
	//������߾���
	RECT m_rRect;
public:
	CItems();
	virtual ~CItems();
	//��õ��߷�����
	virtual int GetDefence();
	//��õ��߹���
	virtual int GetAtt();
	//��õ���Ѫ��
	virtual int GetHp();
	//�����Ƿ����
	virtual void SetApper(bool apper);
	//�õ���ǰ�Ƿ����
	virtual bool GetApper();
	//���þ���
	virtual void SetRect(RECT r);
	//�õ����ߵ�����
	virtual std::string  GetName();
	//�õ����ߵľ���
	virtual RECT GetRect();
};
#endif