#ifndef _GAMELOGO_H_
#define _GAMELOGO_H_

#include "Scene.h"

class CGameLogo : public CScene
{
	//����LOGO���ֵ�ʱ��
	int m_iTime;
public:
	//������ʼ��
	virtual void Init();
	//���
	virtual void OutputRun(); 
	//�߼�����
	virtual void LogicInputRun(); 
	//���볡��
	virtual void Enter();
};

#endif