#include <windows.h>
#include "GameEngine.h"
#include <time.h>
#include "SceneGameStage1.h"
#include "SceneGameStage2.h"
#include "SceneGameBegin.h"
#include "GameLogo.h"
#include "Enter1.h"
#include "Quit1.h"
#include "Enter2.h"
#include "Quit2.h"
#include "Enter3.h"
#include "Quit3.h"
#include "Enter4.h"
#include "Quit4.h"

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	srand((unsigned int)time(0));
	CGameEngine::GetGE()->Init(800, 600);

	CGameEngine::GetGE()->LoadSceneChange("��1", new CEnter1);
	CGameEngine::GetGE()->LoadSceneChange("��1", new CQuit1);
	CGameEngine::GetGE()->LoadSceneChange("��2", new CEnter2);
	CGameEngine::GetGE()->LoadSceneChange("��2", new CQuit2);
	CGameEngine::GetGE()->LoadSceneChange("��3", new CEnter3);
	CGameEngine::GetGE()->LoadSceneChange("��3", new CQuit3);
	CGameEngine::GetGE()->LoadSceneChange("��4", new CEnter4);
	CGameEngine::GetGE()->LoadSceneChange("��4", new CQuit4);

	CGameEngine::GetGE()->LoadScene("��Ϸ��ʼ", new CSceneGameBegin);
	CGameEngine::GetGE()->LoadScene("�ؿ�1", new CSceneGameStage1);
	CGameEngine::GetGE()->LoadScene("�ؿ�2", new CSceneGameStage2);

	CGameEngine::GetGE()->SetInitScene("��Ϸ��ʼ");

	CGameEngine::GetGE()->Run();

	return 1;
}