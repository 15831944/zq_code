#include <windows.h>

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
						char buf[32];
						*((short*)buf) = 32;
						SendMessageA(g_hwnd[1],EM_GETLINE,0,(__w64 long)buf);
						SetWindowTextA(g_hwnd[2],buf);
						break;
					}
				case 4:
					{
						SetWindowTextA(g_hwnd[1],"");
						SetWindowTextA(g_hwnd[2],"");
						break;
					}
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
							350,
							HWND_DESKTOP,
							0,
							wc.hInstance,
							0);
	g_hwnd[1] =  CreateWindow(L"edit",
							  L"",
							 WS_VISIBLE | WS_CHILD |WS_BORDER,
							 0,
							 0,
							 200,
							 25,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)1,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[2] =  CreateWindow(L"edit",
							  L"",
							 WS_VISIBLE | WS_CHILD |WS_BORDER|ES_READONLY ,
							 200,
							 25,
							 200,
							 25,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)2,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[3] =  CreateWindow(L"button",
							  L"����",
							 WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
							 0,
							 60,
							 60,
							 40,
							 g_hwnd[0],//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 (HMENU)3,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);
	g_hwnd[3] =  CreateWindow(L"button",
							  L"���",
							 WS_VISIBLE | WS_CHILD |BS_PUSHBUTTON,
							 0,
							 120,
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