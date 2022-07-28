#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "TcpClient.h"
#include <windows.h>
#include <string>
#include "Map.h"
#include "GameInput.h"
#include "GameOutput.h"
#include "AudioManager.h"

class CScene;

class CGameEngine
{
	static CGameEngine* m_GE;
	int m_ClientW, m_ClientH;
	int m_SleepTime;
	WNDCLASS m_WndClass;
	HWND m_hWnd;
	BOOL m_Active;
	POINT m_PrePos;
	bool m_DB; //˫�ֽڱ�־
	char m_HeadByte; //˫�ֽ��������ֽ�

	//�������
	CGameInput* m_Input;
	CGameOutput* m_Output;
	CAudioManager* m_AudioManager;
	CTcpClient m_TcpClient;

	//�����������
	CMap<std::string, CScene*> m_Scenes; //����ӳ��
	CScene* m_CurScene; //��ǰ����
	CScene* m_NextScene; //��һ������

	CGameEngine();
	CGameEngine(const CGameEngine& that);
	~CGameEngine();

	//���������Ϣ�������Ǿ�̬�Ļ�����ô��ʵ��ʽ����
	//��5��������һ��CGameEngine* this����ô�ͺ�WNDPROC
	//��ƥ���ˣ�����дΪ��̬��Ա����
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	bool Init(int ClientW, int ClientH, int SleepTime);
	void Run();

	//�õ�����
	static CGameEngine* GetGE();

	//�õ�����
	CGameInput* GetInput();
	CGameOutput* GetOutput();
	CAudioManager* GetAudioManager();
	CTcpClient* GetTcpClient();

	//������غ���
	bool LoadScene(const char* id, CScene* pScene);
	bool SetFirstScene(const char* id);
	bool SetCurScene(const char* id);
	CScene* GetScene(const char* id);
	void Exit();

	//����
	static int GetRandomInt(int min, int max);
};

#endif