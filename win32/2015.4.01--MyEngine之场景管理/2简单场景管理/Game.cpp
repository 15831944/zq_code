#include "Game.h"
#include "SceneManager.h"
#include <iostream>
#include <windows.h>

void CGame::Run()
{
	system("cls");
	std::cout<<"Game����"<<std::endl;

	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		CSceneManager::SetCurScene(0);
}