#ifndef _GAMEENGINE_H_
#define _GAMEENGINE_H_

#include <windows.h>
#include <string>
#include <map>

#include "GameInput.h"
#include "GameOutput.h"

class CScene;
class CSceneChange;

class CGameEngine
{
	//�������
	WNDCLASSA m_WndClass;
	char m_WndClassName[32];
	HWND m_hWnd;
	int m_iClientW;
	int m_iClientH;
	BOOL m_Act;
	int m_iSleepTime;//����ʱ��

	//�������
	CGameInput* m_pGI;
	CGameOutput* m_pGO;

	//�������
	std::map<std::string,CScene*> m_Scene;//��������ָ��ӳ��
	CScene* m_pCurScene;//��ǰ����
	CScene* m_pNextScene;//�¸�����

	//��Ϣ������
	static LRESULT CALLBACK _WindPorc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	//�������� 
	//����ģʽ
	//������������ֻ��һ������
	//�乹�������������˽�е�
	//������һ�������ָ�룬���ұ�����˽�еľ�̬��Ա
	//������һ�����еľ�̬��Ա�������������ؾ�̬��ָ��
	CGameEngine();
	~CGameEngine();
	static CGameEngine* m_pGameEngine;

	int m_iRunState;//����״̬

	//�л����
	CSceneChange* m_pEnterChange;
	CSceneChange* m_pQuitChange;

	std::map<std::string,CSceneChange*> m_SceneChange;//�����л�

public:
	//�õ���Ϸ����
	static CGameEngine* GetGE();
	//{
	//	m_pGameEngine = new CGameEngine;
	//	return m_pGameEngine;
	//}

	//��ʼ��
	bool Init(int ClientW,int ClientH);

	//����
	void Run();

	//�������
	bool LoadScene(const char* id,CScene* pScene);

	bool ReleaseScene(const char* id);

	bool SetInitScene(const char* id);

	bool SetCurScene(const char* id);

	CScene* GetScene(const char* id);

	//�������
	CGameInput* GetGI();
	CGameOutput* GetGO();
	void SetTitle(const char* Title);
	bool SetSleepTime(int SleepTime);
	
	void ExitGame();

	int GetW();

	int GetH();

	//���س����л�
	bool LoadSceneChange(const char* id,CSceneChange* pSceneChange);
};

#endif