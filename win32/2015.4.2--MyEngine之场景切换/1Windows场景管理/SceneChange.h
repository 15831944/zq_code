#ifndef _SCENECHANGE_H_
#define _SCENECHANGE_H_

class CSceneChange
{
	friend class CGameEngine;
	int m_iAllFrame;//��֡��
	int m_iCurFrame;//��ǰ֡��
public:
	CSceneChange(int AllFrame);
	void SetBegin();
	virtual void Render(int CurFrame);
};

#endif