#ifndef _SCENE_H_
#define _SCENE_H_
//CStartScene:��ʼ����
//CEndScene:��������
//CGameScene:��Ϸ����
//CSetScene:��Ϸ���ó���

//CSceneManager:��������
//������

class CSceneManager;
class CScene
{
	CSceneManager* pCSceneManager;
public:
	virtual void Run();
	virtual void SetSceneManager(CSceneManager* pSceneManager);
	virtual CSceneManager* GetManager();

};

#endif