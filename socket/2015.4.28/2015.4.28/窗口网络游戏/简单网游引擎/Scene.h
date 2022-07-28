#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include "Map.h"
#include "TcpClient.h"

class CUI;

class CScene
{
	friend class CGameEngine;

protected:
	CMap<std::string, CUI*> m_UIs;
	CUI* m_KeyUI; //ӵ�м��̽���Ŀؼ�

public:
	CScene();
	virtual ~CScene();

	//ֻ�������ʱ��ִ��һ�α�����Init����
	virtual void Init();

	//���������������뵽��������ʱ��ִ�б�����Enter����
	virtual void Enter();

	//��������롢�߼�
	virtual void OutputRun();
	virtual void InputRun();
	virtual void LogicRun();

	//���ӱ��������뵽����������ʱ��ִ�б�����Quit����
	virtual void Quit();

	//ֻ������ʱ��ִ��һ�α�����End����
	virtual void End();

	//UI���
	bool LoadUI(CUI* pUI, const char* id);
	CUI* GetUI(const char* id);
	bool SetKeyUI(const char* id);
	CUI* GetKeyUI();
	virtual void OnUIMessage(int message, const char* id);

	//�������
	virtual void OnNetEvent(_TC_NET_EVENT* ptne);
};

#endif