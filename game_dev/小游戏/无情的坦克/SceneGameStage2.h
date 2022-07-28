#ifndef _SCENE_GAMESTAGE_2_H_
#define _SCENE_GAMESTAGE_2_H_

#include "Scene.h"
#include "GameLogic.h"
class CSceneGameStage2 : public CScene
{
	//��Ϸ�Ƿ����
	bool m_bGameEnd;
	//��Ϸ�Ƿ�ʤ��
	bool m_bGameVictor;
	//ͼƬ����ʱ��
	int m_iTime;
	//�Ƿ�ͨ�������������Ϸ
	bool m_bIsRead;
	//�ؿ�
	int m_iStage;
	//�Ƿ񲥷���Ϸʧ�ܵ�����
	bool m_bBoFangshibai;
	//�Ƿ񲥷���Ϸʤ��������
	bool m_bBoFangWin;
	//�߼������
	CGameLogic  stage2;
public:
	//��ʼ������
	virtual void Init();
	//���볡��
	virtual void Enter();
	//���
	virtual void OutputRun(); 
	//�߼����
	virtual void LogicInputRun(); 
	//�˳�
	virtual void Quit();
	//�Ƿ�ͨ����Ϸ��ȡ�������Ϸ
	virtual void SetRead(bool set);
	//UI��Ϣ
	virtual void OnUIMsg(const char* id, int UIMSG);
	//��ȡ�߼������
	CGameLogic* GetLogicObject();
};

#endif