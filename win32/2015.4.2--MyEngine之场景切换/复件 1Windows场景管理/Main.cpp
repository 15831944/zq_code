#include <windows.h>
#include "GameEngine.h"	
#include "2.h"
#include "1.h"


int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	CGameEngine::GetGE()->Init(640,480);
	CGameEngine::GetGE()->LoadScene("��ʼ����",new C1);
	CGameEngine::GetGE()->LoadScene("��Ϸ����",new C2);
	CGameEngine::GetGE()->SetInitScene("��ʼ����");
	CGameEngine::GetGE()->Run();
	return 1;
}