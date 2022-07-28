#include "GameEngine.h"	
#include "SceneChange.h"
#include "Scene.h"
#include <time.h>
#include <iostream>

#define _SC_NONE 0 //û���л�
#define _SC_QUIT 1 //׼�����л�
#define _SC_CHANGE 2 //�л�����
#define _SC_ENTER 3 //׼�����л�

CGameEngine* CGameEngine::m_pGameEngine = 0;
LRESULT CALLBACK CGameEngine::_WindPorc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_ACTIVATEAPP:
		{
			GetGE()->m_Act = (BOOL)wParam;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
 
	//�������� 
	//����ģʽ
	//������������ֻ��һ������
	//�乹�������������˽�е�
	//������һ�������ָ�룬���ұ�����˽�еľ�̬��Ա
	//������һ�����еľ�̬��Ա�������������ؾ�̬��ָ��
CGameEngine::CGameEngine()
:
m_hWnd(0),
m_iClientW(0),
m_iClientH(0),
m_Act(TRUE),
m_iSleepTime(33),
m_pGI(0),
m_pGO(0),
m_pCurScene(0),
m_pNextScene(0),
m_iRunState(_SC_NONE),
m_pEnterChange(0),
m_pQuitChange(0)
{
	srand((unsigned int)time(0));
}
CGameEngine::~CGameEngine()
{}

CGameEngine* CGameEngine::GetGE()
{
	if(0 == m_pGameEngine)
		m_pGameEngine = new CGameEngine;
	return m_pGameEngine;
}

	//��ʼ��
bool CGameEngine::Init(int ClientW,int ClientH)
{
	if(ClientW < 1 || ClientH < 1)
		return false;
	//�õ����
	m_iClientW = ClientW;
	m_iClientH = ClientH;

	m_WndClass.style = CS_HREDRAW|CS_VREDRAW;
	m_WndClass.lpfnWndProc = _WindPorc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0,IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0,IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;

	for(int i = 0; i < 31; ++i)
	{
		m_WndClassName[i] = rand() % 26 + 'a';
	}
	m_WndClassName[31] = 0;

	m_WndClass.lpszClassName = m_WndClassName;
	RegisterClass(&m_WndClass);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - m_iClientW) / 2,
		(sh - m_iClientH) / 2,
		(sw - m_iClientW) / 2 + m_iClientW,
		(sh - m_iClientH) / 2 + m_iClientH
	};

	AdjustWindowRect(&r,
		WS_OVERLAPPED | WS_CAPTION 
		| WS_SYSMENU | WS_MINIMIZEBOX ,
		FALSE);

	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION 
		| WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);

	m_pGI = new CGameInput(m_hWnd);
	m_pGO = new CGameOutput(m_hWnd);
	//m_pEnterChange = new 
	return true;
}

//����
void CGameEngine::Run()
{
	std::map<std::string, CScene*>::iterator i;
	//������ʼ��
	for(i = m_Scene.begin(); i != m_Scene.end();++i)
		i->second->Init();//��̬

	if(m_pCurScene)
		m_pCurScene->Enter();

	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(m_Act)
		{
			int bt = GetTickCount();
			m_pGO->Begin();
			if(m_pCurScene)
			{
				m_pCurScene->OutputRun();
				switch(m_iRunState)
				{
				case _SC_QUIT:
					{
						if(m_pQuitChange)
						{
							m_pQuitChange->Render(m_pQuitChange->m_iCurFrame += 1);
							if(m_pQuitChange->m_iCurFrame == m_pQuitChange->m_iAllFrame)
								m_iRunState = _SC_CHANGE;
						}
						else
							m_iRunState = _SC_CHANGE;
						break;
					}
				case _SC_ENTER:
					{
						if(m_pEnterChange)
						{
							m_pEnterChange->Render(m_pEnterChange->m_iCurFrame += 1);
							if(m_pEnterChange->m_iCurFrame == m_pEnterChange->m_iAllFrame)
								m_iRunState = _SC_NONE;
						}
						else
							m_iRunState = _SC_NONE;
						break;
					}
				}
			}
			m_pGO->End();
			
			m_pGI->Run();
			if(m_pCurScene && m_iRunState == _SC_NONE)
				m_pCurScene->LogicInputRun();

			int at = GetTickCount() - bt;
			Sleep((m_iSleepTime > at) ? (m_iSleepTime - at) : 1);
		}
		else
		{
			WaitMessage();
		}

		if(m_pNextScene && m_iRunState == _SC_CHANGE)
		{
			m_pCurScene->Quit();
			m_pCurScene = m_pNextScene;
			m_pCurScene->Enter();
			m_pNextScene = 0;
			m_iRunState = _SC_ENTER;
		}
	}

	if(m_pCurScene)
	{
		m_pCurScene->Quit();
	}
	for(i = m_Scene.begin(); i != m_Scene.end();++i)
	{
		i->second->End();
		delete i->second;
	}

	std::map<std::string , CSceneChange*>::iterator j;
	for(j = m_SceneChange.begin() ; j != m_SceneChange.end();++j)
		delete j->second;
	delete m_pGO;
	delete m_pGI;
	delete m_pGameEngine;
}

//�������
bool CGameEngine::LoadScene(const char* id,CScene* pScene)
{
	std::string s = id;
	if(m_Scene.find(s) != m_Scene.end())
		return false;
	m_Scene.insert(std::pair<std::string,CScene*>(s,pScene));
	return true;
}

bool CGameEngine::ReleaseScene(const char* id)
{
	std::string s = id;
	std::map<std::string,CScene*>::iterator i = m_Scene.find(s);
	if(i == m_Scene.end())
		return false;
	i->second->End();
	delete i->second;
	m_Scene.erase(i);
	return true;
}

bool CGameEngine::SetInitScene(const char* id)
{
	std::string s = id;
	std::map<std::string,CScene*>::iterator i = m_Scene.find(s);
	if(i == m_Scene.end())
		return false;
	m_pCurScene = i->second;
	return true;
}

bool CGameEngine::SetCurScene(const char* id)
{
	std::string s = id;
	std::map<std::string,CScene*>::iterator i = m_Scene.find(s);
	if(i == m_Scene.end())
		return false;
	m_pNextScene = i->second;

	std::map<std::string, CSceneChange*>::iterator j;

	j = m_SceneChange.find(m_pCurScene->m_QuitChange);
	if(j == m_SceneChange.end())
		m_pQuitChange = 0;
	else
	{
		m_pQuitChange = j->second;
		m_pQuitChange->SetBegin();
	}

	j = m_SceneChange.find(m_pNextScene->m_EnterChange);
	if(j == m_SceneChange.end())
		m_pEnterChange = 0;
	else
	{
		m_pEnterChange = j->second;
		m_pEnterChange->SetBegin();
	}

	m_iRunState = _SC_QUIT;

	return true;
}

CScene* CGameEngine::GetScene(const char* id)
{
	std::string s = id;
	std::map<std::string,CScene*>::iterator i = m_Scene.find(s);
	if(i == m_Scene.end())
		return 0;
	return i->second;
}

//�������
CGameInput* CGameEngine::GetGI()
{
	return m_pGI;
}
CGameOutput* CGameEngine::GetGO()
{
	return m_pGO;
}
void CGameEngine::SetTitle(const char* Title)
{
	SetWindowTextA(m_hWnd,Title);
}
bool CGameEngine::SetSleepTime(int SleepTime)
{
	if(SleepTime < 1)
		return false;
	m_iSleepTime = SleepTime;
	return true;
}

void CGameEngine::ExitGame()
{
	PostQuitMessage(0);
}

int CGameEngine::GetW()
{
	return m_iClientW;
}

int CGameEngine::GetH()
{
	return m_iClientH;
}

bool CGameEngine::LoadSceneChange(const char* id,CSceneChange* pSceneChange)
{
	std::string s = id;
	if(m_SceneChange.find(s) != m_SceneChange.end())
		return false;

	m_SceneChange.insert(std::pair<std::string,CSceneChange*>(s,pSceneChange));
	return true;
}