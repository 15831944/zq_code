#include "Game.h"
#include "Main.h"

#include "ddraw.h"
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

LPDIRECTDRAW7 dd; //ddraw����


void Init()
{
	if (DD_OK != DirectDrawCreateEx(0, (void**)&dd, IID_IDirectDraw7, 0))
		return;

	//DDSCL_ALLOWREBOOT:������ȫ������ʹ��Ctrl+Alt+Del
	//DDSCL_EXCLUSIVE:��ռģʽ��ֵ����ddraw������ȫ��ռ��ʾ��
	//DDSCL_FULLSCREEN:ȫ��ģʽ
	if (DD_OK != dd->SetCooperativeLevel(g_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))
		return;

	dd->SetDisplayMode(640, 480, 32, 0, 0);
}

void Run()
{
	
}

void End()
{
	if (dd)
		dd->Release();
}