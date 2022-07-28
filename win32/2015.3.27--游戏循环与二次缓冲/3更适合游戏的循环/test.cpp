#include <windows.h>
#include "UseBmp.h"

BOOL g_Act = TRUE;//���ڼ����־

HDC g_mainDC;//����ʾ�豸

POINT g_hero;

HDC g_bmpdc;

void GameInit(HWND hwnd)
{
	//��ȡ����ʾ�豸
	g_mainDC = GetDC(hwnd);

	g_hero.x = 150;
	g_hero.y = 240;

	g_bmpdc = GetBmpDC(hwnd,"0.bmp");
}

void GameRun()
{
	BitBlt(g_mainDC,0,0,640,480,g_bmpdc,0,0,SRCCOPY);
	Rectangle(g_mainDC,g_hero.x,g_hero.y,g_hero.x + 20,g_hero.y + 20);

	if(GetAsyncKeyState(VK_UP) & 0x8000)
		g_hero.y -= 5;
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		g_hero.y += 5;
	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		g_hero.x -= 5;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		g_hero.x += 5;
	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC);
	DeleteBmpDC(g_bmpdc);
}


//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
			return 0;
		}
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//01)���һ���������Ľṹ��
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - 640) / 2,
		(sh - 480) / 2,
		(sw - 640) / 2 + 640,
		(sh - 480) / 2 + 480
	};

	AdjustWindowRect(&r,WS_OVERLAPPED | WS_CAPTION
		|WS_SYSMENU,FALSE);

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "���ʺ���Ϸ��ѭ��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	//�鿴��ǰ��Ϣ�����еĶ�ͷ��Ϣ��
	//���Ĳ�������ָ���Ƿ�ɾ���õ���
	//��ͷ��Ϣ,������û����Ϣ��PeekMessage
	//�����̷��أ�ֻ����������Ϣ������
	//û����Ϣ���ؼ�
	//PeekMessage(
 //   LPMSG lpMsg,//���ڵõ���Ϣ�Ľṹ���ַ
 //   HWND hWnd,//ָ���õ���Ϣ�Ĵ��ڣ�Ϊ0���ʾ�õ����̵߳����д�����Ϣ
 //   UINT wMsgFilterMin,//��Ϣ���˵�������
 //   UINT wMsgFilterMax,//��Ϣ���˵�������
 //   UINT wRemoveMsg);//PM_REMOVE��ʾ�Ƴ��õ��Ķ�ͷ��Ϣ,PM_NOREMOVE��ʾ���Ƴ�

	GameInit(hWnd);
	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		//�������Ϣ�ʹ�����Ϣ
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//���û����Ϣ�Ҵ����Ǽ���״̬�ʹ�����Ϸѭ��
		else if(g_Act)
			GameRun();
		else
			WaitMessage();
	}

	GameEnd(hWnd);

	return 1;
}