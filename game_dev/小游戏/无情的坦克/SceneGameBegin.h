#ifndef _SCENE_GAMEBEGIN_H_
#define _SCENE_GAMEBEGIN_H_

#include "Scene.h"


class CSceneGameBegin : public CScene
{
	bool m_bJieShaoTu;
public:
	//������ʼ��
	virtual void Init();
	//��������
	virtual void Enter();
	//���
	virtual void OutputRun(); 
	//�߼�����
	virtual void LogicInputRun();
	//�Ƴ�����
	virtual void Quit();
	//UI��Ϣ
	void OnUIMsg(const char* id, int UIMSG);
};

#endif