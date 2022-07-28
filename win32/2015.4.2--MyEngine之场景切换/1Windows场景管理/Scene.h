#ifndef _SCENE_H_
#define _SCENE_H_
#include <string>
class CScene
{
	friend class CGameEngine;
	std::string m_EnterChange;
	std::string m_QuitChange;
public:
	CScene();
	virtual ~CScene();
	virtual void Init();
	virtual void Enter();
	virtual void OutputRun();//����
	virtual void LogicInputRun();//�߼�����
	virtual void Quit();
	virtual void End();

	//�л����
	void SetEnterChange(const char* id);
	void SetQuitChange(const char* id);
};

#endif