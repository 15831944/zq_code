#include <windows.h>

HWND g_hWnd[5];
#define _BUTTON1 0
#define _BUTTON2 1

RECT rButton1;
RECT rButton2;

__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPa
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			
			return 0;
		}
	case WM_CLOSE:
		{
			if(hwnd == g_hWnd[0])
				DestroyWindow(hwnd);
			else
				ShowWindow(hwnd,SW_HIDE);
			return 0;
		}
	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc =BeginPaint(hwnd,&ps);
			
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_COMMAND:
		{
			if(BN_CLICKED == HIWORD(wParam))
			{
				if(LOWORD(wParam) == _BUTTON1)
					ShowWindow(g_hWnd[1],SW_SHOW);
				if(LOWORD(wParam) == _BUTTON2)
					ShowWindow(g_hWnd[2],SW_SHOW);
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			if(PtInRect(&rButton1,p))
			{
				SendMessage(g_hWnd[3],BM_CLICK,0,0);
			}
			if(PtInRect(&rButton2,p))
			{
				SendMessage(g_hWnd[4],BM_CLICK,0,0);
			}
			return 0;
		}
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon =LoadIcon(0,IDI_APPLICATION);
	wc.hCursor =LoadCursor(0,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName =L"�˰�";
	RegisterClass(&wc);
	g_hWnd[0] = CreateWindow(wc.lpszClassName,
							L"�����߶�",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	g_hWnd[1] = CreateWindow(wc.lpszClassName,
							 L"�Ӵ���",
							 WS_OVERLAPPEDWINDOW  | WS_CHILD,
							 100,//���ڵ����Ͻ�x����
							 100,//���ڵ����Ͻ�y����
							 500,//���ڵĿ����أ�
							 200,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	g_hWnd[2] = CreateWindow(wc.lpszClassName,
							 L"��������",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 0,
							 wc.hInstance,
							 0);
	g_hWnd[3] = CreateWindow(L"button",
							 L"���Ӵ���",
							 WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 25,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON1,
							 wc.hInstance,
							 0);
	rButton2.left = 0;
	rButton2.top = 0;
	rButton2.right = 100;
	rButton2.bottom = 25;
	g_hWnd[4] = CreateWindow(L"button",
							 L"���������",
							 WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
							 0,//���ڵ����Ͻ�x����
							 40,//���ڵ����Ͻ�y����
							 100,//���ڵĿ����أ�
							 25,//���ڵĸߣ����أ�
							 g_hWnd[0],
							 (HMENU)_BUTTON2,
							 wc.hInstance,
							 0);
	rButton1.left = 0;
	rButton1.top = 40;
	rButton1.right = 100;
	rButton1.bottom = 40+25;
	ShowWindow(g_hWnd[0],nCmdShow);
	UpdateWindow(g_hWnd[0]);
	
	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 1;
}