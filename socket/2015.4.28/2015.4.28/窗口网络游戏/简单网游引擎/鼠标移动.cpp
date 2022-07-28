#include <iostream>
#include "GameEngine.h"
#include "Begin.h"
#include "Game.h"

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	CGameEngine::GetGE()->Init(640, 480, 33);

	CGameEngine::GetGE()->LoadScene("��ʼ����", new CBegin);
	CGameEngine::GetGE()->LoadScene("��Ϸ����", new CGame);
	CGameEngine::GetGE()->SetFirstScene("��ʼ����");
	CGameEngine::GetGE()->Run();

	return 1;
}