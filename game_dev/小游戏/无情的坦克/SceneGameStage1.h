#ifndef _SCENE_GAMESTAGE1_H_
#define _SCENE_GAMESTAGE1_H_

#include "Scene.h"
#include "GameLogic.h"
class CSceneGameStage1 : public CScene
{
	//��Ϸ�Ƿ����
	bool m_bGameEnd;
	//���ơ���һ�ء�����ͼƬ��ʱ��
	int m_iTime;
	//�Ƿ�Ϊ��ȡ�浵������Ϸ
	bool m_bIsRead;
	//��ǰ�ؿ�
	int m_iStage;
	//�߼������
	CGameLogic  stage1;
	//�Ƿ񲥷���������
	bool m_bBoFang;
public:
	//������ʼ��
	void Init();
	//��������
	void Enter();
	//���
	void OutputRun(); 
	//�߼�����
	void LogicInputRun(); 
	//�˳�����
	void Quit();
	void SetRead(bool set);
	bool GetSetRead();
	//UI��Ϣ
	void OnUIMsg(const char* id, int UIMSG);
	//����߼���ָ��
	CGameLogic* GetLogicObject();
};

#endif