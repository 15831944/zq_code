#ifndef _UI_H_
#define _UI_H_

#include "cocos2d.h"

using namespace cocos2d;

class CGameLayer;

#define _UE_IN_DOWN 0 //�ڲ�����
#define _UE_IN_UP 1 //�ڲ�̧��
#define _UE_OUT_DOWN 2 //�ⲿ����
#define _UE_OUT_UP 3 //�ⲿ̧��

class CUI
{
public:
	CCRect m_Rect; //λ�úͳߴ�
	bool m_Visible; //�ɼ���
	bool m_Active; //������
	int m_ID; //��ʾ
	CGameLayer* m_Layer; //��

	//����
	CUI(const CCRect& r,
		bool v = true,
		bool a = true);

	//����
	virtual ~CUI();

	//�麯��
	virtual void Enter();
	virtual void Render();
	virtual void OnMessage(int e, int x, int y);
	virtual void Exit();
};

#endif