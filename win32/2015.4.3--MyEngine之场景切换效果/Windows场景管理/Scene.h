#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <map>
class CUI;
class CScene
{
	friend class CGameEngine;

	//����л�����
	std::string m_EnterChange;
	std::string	m_QuitChange;

	//�ؼ������
	std::map<std::string,CUI*> m_UI;
public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Enter();
	virtual void OutputRun(); //����
	virtual void LogicInputRun(); //�߼�������
	virtual void Quit();
	virtual void End();

	//�л����
	void SetEnterChange(const char* id);
	void SetQuitChange(const char* id);

	//�ؼ����
	//�������
	//ж�����
	//�õ��ؼ�
};

#endif