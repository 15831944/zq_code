//------------------------
//CGameRole:��ϷԪ��(��ɫ)��
//��Ҫ������Ϸ�е��ˣ�ľ�����ӣ����������ϰ�
//��Щ��ϷԪ�صĹ���:���꣬����
//�÷���ͨ����Ϸ�߼��������غ���
//���ߣ��»�� ���ڣ�2015��3��13��
//------------------------

#ifndef _GAMEROLE_H_
#define _GAMEROLE_H_

#include "GameTool.h"

//��ϷԪ��(��ɫ)��
class CGameRole
{
	int m_iX;//��ɫ��X����
	int m_iY;//��ɫ��Y����
	Role m_role;//��ɫ�����ͣ�ö��
public:
	//��Ϸ��ɫ��ʼ������,x,y,r����x���꣬y���꣬r��ɫ����
	void Init(int x,//x����
			  int y,//y����
			  Role r);//��ɫ����
	//�������ú���
	void SetZuoBiao(int x,int y);

	//���ý�ɫ����
	void SetEnumRole(Role r);

	//��ȡ��ɫ��X����
	int GetZBX();

	//��ȡ��ɫ��Y����
	int GetZBY();

	//��ȡ��ɫ����
	Role GetRole();
};

#endif