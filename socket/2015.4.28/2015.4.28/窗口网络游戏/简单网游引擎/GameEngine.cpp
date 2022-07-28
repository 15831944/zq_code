#include <time.h>
#include "GameEngine.h"
#include "Scene.h"
#include "UI.h"

CGameEngine* CGameEngine::m_GE = 0;

CGameEngine::CGameEngine()
:
m_hWnd(0),
m_Active(TRUE),
m_Input(0),
m_Output(0),
m_CurScene(0),
m_NextScene(0)
{}

CGameEngine::CGameEngine(const CGameEngine& that)
{}

CGameEngine::~CGameEngine()
{}

LRESULT CALLBACK CGameEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		{
			if (GetGE()->m_CurScene)
			{
				//�õ����εĹ��λ��
				POINT CurPos = {LOWORD(lParam), HIWORD(lParam)};

				//ѭ���ó���������UI
				for (int i = 0; i < GetGE()->m_CurScene->m_UIs.Length(); ++i)
				{
					CUI* pUI = GetGE()->m_CurScene->m_UIs.At(i)->data;

					//״̬�ж�
					if (pUI->GetVisible() && pUI->GetEnable())
					{
						//��ǰUI����
						RECT r = {pUI->m_X, pUI->m_Y, pUI->m_X + pUI->m_W, pUI->m_Y + pUI->m_H};

						//�õ�����ϴΡ������뵱ǰUI���ε���ײ��ϵ
						BOOL b1 = PtInRect(&r, GetGE()->m_PrePos);
						BOOL b2 = PtInRect(&r, CurPos);

						if (b1 && b2)
							pUI->OnEvent(_UIE_CURSOR_MOVE_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else if (b1 && !b2)
							pUI->OnEvent(_UIE_CURSOR_QUIT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else if (!b1 && b2)
							pUI->OnEvent(_UIE_CURSOR_ENTER, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
						else
							pUI->OnEvent(_UIE_CURSOR_MOVE_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y);
					}
				}

				//������λ������Ϊ��һ�ε�ǰ��λ��
				GetGE()->m_PrePos = CurPos;
			}

			return 0;
		}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		{
			if (GetGE()->m_CurScene)
			{
				//�õ����εĹ��λ��
				POINT CurPos = {LOWORD(lParam), HIWORD(lParam)};

				//ѭ���ó���������UI
				for (int i = 0; i < GetGE()->m_CurScene->m_UIs.Length(); ++i)
				{
					CUI* pUI = GetGE()->m_CurScene->m_UIs.At(i)->data;

					//״̬�ж�
					if (pUI->GetVisible() && pUI->GetEnable())
					{
						//��ǰUI����
						RECT r = {pUI->m_X, pUI->m_Y, pUI->m_X + pUI->m_W, pUI->m_Y + pUI->m_H};

						//�õ������뵱ǰUI���ε���ײ��ϵ
						BOOL b = PtInRect(&r, CurPos);
						
						//������ײ��ϵ���в�ͬ�Ĵ���
						if (b)
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: pUI->OnEvent(_UIE_L_DOWN_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_LBUTTONUP: pUI->OnEvent(_UIE_L_UP_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONDOWN: pUI->OnEvent(_UIE_R_DOWN_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONUP: pUI->OnEvent(_UIE_R_UP_IN, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							}
						}
						else
						{
							switch (uMsg)
							{
							case WM_LBUTTONDOWN: pUI->OnEvent(_UIE_L_DOWN_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_LBUTTONUP: pUI->OnEvent(_UIE_L_UP_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONDOWN: pUI->OnEvent(_UIE_R_DOWN_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							case WM_RBUTTONUP: pUI->OnEvent(_UIE_R_UP_OUT, CurPos.x - pUI->m_X, CurPos.y - pUI->m_Y); break;
							}
						}
					}
				}
			}

			return 0;
		}
	case WM_KEYDOWN:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_K_DOWN, (int)wParam, 0);
			}

			return 0;
		}
	case WM_KEYUP:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_K_UP, (int)wParam, 0);
			}

			return 0;
		}
	case WM_CHAR:
		{
			if (GetGE()->m_CurScene &&
				GetGE()->m_CurScene->m_KeyUI &&
				GetGE()->m_CurScene->m_KeyUI->GetVisible() &&
				GetGE()->m_CurScene->m_KeyUI->GetEnable())
			{
				//����Ѿ��յ����ֽ����ֵ����ֽ�
				if (GetGE()->m_DB)
				{
					//���֮ǰ���ֽں͵�ǰ���ֽ�
					int c = 0;
					((char*)&c)[0] = GetGE()->m_HeadByte;
					((char*)&c)[1] = (char)wParam;

					//����˫�ֽ�����
					GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_CHAR, c, 1);
					GetGE()->m_DB = false;
					return 0;
				}

				//�ж��Ƿ���˫�ֽ����ֵ����ֽ�
				if (IsDBCSLeadByte((char)wParam))
				{
					GetGE()->m_HeadByte = (char)wParam;
					GetGE()->m_DB = true;
				}
				else
				{
					//���뵥�ֽ�����
					GetGE()->m_CurScene->m_KeyUI->OnEvent(_UIE_CHAR, (char)wParam, 0);
				}
			}

			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			GetGE()->m_Active = (BOOL)wParam;
			return 0;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool CGameEngine::Init(int ClientW, int ClientH, int SleepTime)
{
	srand((unsigned int)time(0));

	//�������
	if (ClientW < 1 || ClientH < 1 || SleepTime < 1)
		return false;

	//�õ�����
	m_ClientW = ClientW;
	m_ClientH = ClientH;
	m_SleepTime = SleepTime;

	//��䴰�����ṹ��
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = WindowProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND ;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = __TEXT("gamfe-cd-cx-66");

	//ע�ᴰ�����ṹ��
	RegisterClass(&m_WndClass);

	//��������
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT rclient
		=
	{
		(sw - m_ClientW) / 2,
		(sh - m_ClientH) / 2,
		rclient.left + m_ClientW,
		rclient.top + m_ClientH
	};
	AdjustWindowRect(&rclient, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		rclient.left,
		rclient.top,
		rclient.right - rclient.left,
		rclient.bottom - rclient.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);

	//��ʼ������
	m_Input = new CGameInput(m_hWnd);
	m_Output = new CGameOutput(m_hWnd);
	m_AudioManager = new CAudioManager;

	//�õ����λ��
	GetCursorPos(&m_PrePos);
	ScreenToClient(m_hWnd, &m_PrePos);

	//����˫�ֽڱ�ʾΪ��
	m_DB = false;

	return true;
}

void CGameEngine::Run()
{
	//��ʼ�����г���
	for (int i = 0; i < m_Scenes.Length(); ++i)
	{
		//�õ���ǰ����
		CScene* p = m_Scenes.At(i)->data;

		p->Init(); //��ʼ����ǰ��������̬

		for (int j = 0; j < p->m_UIs.Length(); ++j)
			p->m_UIs.At(j)->data->Init(); //��ʼ����ǰ����������UI����̬
	}

	if (m_CurScene)
	{
		m_CurScene->Enter(); //����ĳ������룺��̬

		for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			m_CurScene->m_UIs.At(i)->data->Enter(); //����ĳ���������UI���룺��̬
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		int bt = GetTickCount();

		m_Input->Run();

		//��Ϸѭ��
		if (m_CurScene)
		{
			m_Output->Begin();

			m_CurScene->OutputRun(); //�����������̬

			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			{
				CUI* pUI = m_CurScene->m_UIs.At(i)->data;
				pUI->Render(pUI->GetEnable()); //��ǰ����UI�������̬
			}

			m_Output->End();

			m_CurScene->InputRun(); //�������룺��̬
			m_CurScene->LogicRun(); //�����߼�����̬

			//���粿������
			m_TcpClient.Run();
			_TC_NET_EVENT tne;
			while (m_TcpClient.GetTCNetEvent(&tne))
			{
				//������Ӧ�����¼�����̬
				m_CurScene->OnNetEvent(&tne);
				m_TcpClient.ReleaseTSNetEvent(&tne);
			}
		}

		int at = GetTickCount() - bt;
		Sleep(at < m_SleepTime ? m_SleepTime - at : 1);

		//˵����Ϸѭ��������SetCurScene���ڴ˴�ִ�е�ǰ����
		//ָ��ĸı䣬����ִ������������Quit��Enter��������
		//�赱ǰҪ�ӳ���a�л�������b����ô����ͻ�ִ��a->Quit��
		//��ִ��b->Enter
		if (m_NextScene)
		{
			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
				m_CurScene->m_UIs.At(i)->data->Quit(); //��ǰ��������UI�ĳ�����̬

			m_CurScene->Quit(); //��ǰ�����ĳ�����̬

			m_CurScene = m_NextScene;

			m_CurScene->Enter(); //��ǰ�������룺��̬

			for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
				m_CurScene->m_UIs.At(i)->data->Enter(); //��ǰ��������UI���룺��̬

			m_NextScene = 0;
		}
	}

	if (m_CurScene)
	{
		for (int i = 0; i < m_CurScene->m_UIs.Length(); ++i)
			m_CurScene->m_UIs.At(i)->data->Quit(); //���ĳ���������UI�ĳ�����̬

		m_CurScene->Quit(); //���ĳ����ĳ�����̬
	}

	//�������г���
	for (int i = 0; i < m_Scenes.Length(); ++i)
	{
		//�õ���ǰ����
		CScene* p = m_Scenes.At(i)->data;


		for (int j = 0; j < p->m_UIs.Length(); ++j)
		{
			p->m_UIs.At(j)->data->End(); //������ǰ����������UI����̬
			delete p->m_UIs.At(j)->data; //ɾ��UI
		}

		p->End(); //������ǰ��������̬
		delete p;
	}

	//�ͷŹ���
	delete m_AudioManager;
	delete m_Output;
	delete m_Input;

	delete m_GE;
}

CGameEngine* CGameEngine::GetGE()
{
	if (0 == m_GE)
		m_GE = new CGameEngine;
	return m_GE;
}

CGameInput* CGameEngine::GetInput()
{
	return m_Input;
}

CGameOutput* CGameEngine::GetOutput()
{
	return m_Output;
}

CAudioManager* CGameEngine::GetAudioManager()
{
	return m_AudioManager;
}

CTcpClient* CGameEngine::GetTcpClient()
{
	return &m_TcpClient;
}

bool CGameEngine::LoadScene(const char* id, CScene* pScene)
{
	std::string str = id;
	if (m_Scenes.Find(str))
		return false;

	m_Scenes.Insert(str, pScene);
	return true;
}

bool CGameEngine::SetFirstScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	if (!p)
		return false;
	m_CurScene = p->data; //���õ�ǰ����ָ��
	return true;
}

bool CGameEngine::SetCurScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	if (!p)
		return false;
	m_NextScene = p->data; //������һ������ָ��
	return true;
}

CScene* CGameEngine::GetScene(const char* id)
{
	std::string str = id;
	CMap<std::string, CScene*>::PAIR* p = m_Scenes.Find(str);
	return p ? p->data : 0;
}

void CGameEngine::Exit()
{
	PostQuitMessage(0);
}

int CGameEngine::GetRandomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}