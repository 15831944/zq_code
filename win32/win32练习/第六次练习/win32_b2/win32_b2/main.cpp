#include <windows.h>
#include<iostream>

HWND g_hwnd[5];

__w64 long __stdcall WindowProc(HWND hwnd,unsigned int uMsg,__w64 unsigned int wParam,__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
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
			if(HIWORD(wParam)==BN_CLICKED)
			{
				switch(LOWORD(wParam))
				{
				case 3:
					{
						int r =(int)SendMessageA(g_hwnd[1],EM_GETLINECOUNT,0,0);
						char buf[32];
						sprintf_s(buf,32,"��ǰ����%d��",r);
						MessageBoxA(hwnd,buf,"��ʾ",MB_OK);
						break;
					}
				case 4:
					{
						int r =(int)SendMessageA(g_hwnd[1],EM_GETLINECOUNT,0,0);
						for(int i=0;i<r;i++)
						{
							char buf[256];
							*((short*)buf) = 256;
							SendMessageA(g_hwnd[1],EM_GETLINE,i,(__w64 long)buf);
							char buf2[32];
							sprintf_s(buf2,32,"��%d��",i);
							MessageBoxA(g_hwnd[0],buf,buf2,MB_OK);
						}
						break;
					}
				}
			}else
			if(HIWORD(wParam) == EN_CHANGE)
			{
				if(LOWORD(wParam)==1)
				{
					char buf[256];
					*((short*)buf) = 256;
					int r = (int)SendMessageA(g_hwnd[1],EM_LINEFROMCHAR,-1,0);
					SendMessageA(g_hwnd[1],EM_GETLINE,r,(__w64 long)buf);
					SetWindowTextA(g_hwnd[2],buf);
				}
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
	g_hwnd[0] = CreateWindow(wc.lpszClassName,
							L"�༭��ĸ���",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							700,
							500,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	g_hwnd[1] =  CreateWindow(L"edit",
							  L"",
							  ES_WANTRETURN | ES_AUTOVSCROLL | ES_MULTILINE| ES_AUTOHSCROLL
							 |WS_HSCROLL|WS_VSCROLL
							 | WS_VISIBLE | WS_CHILD | WS_BORDER,
							 0,
							 0,
							 200,
							 200,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)1,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[2] =  CreateWindow(L"edit",
							  L"",
							 WS_VISIBLE | WS_CHILD |WS_BORDER|ES_READONLY|WS_HSCROLL|ES_AUTOHSCROLL|ES_MULTILINE ,
							 200,
							 200,
							 200,
							 50,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)2,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[3] =  CreateWindow(L"button",
							  L"����",
							 WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
							 0,
							 260,
							 60,
							 40,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)3,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[3] =  CreateWindow(L"button",
							  L"����",
							 WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
							 0,
							 320,
							 60,
							 40,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)4,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	
	
	
	ShowWindow(g_hwnd[0],nCmdShow);
	UpdateWindow(g_hwnd[0]);
	
	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 1;
}