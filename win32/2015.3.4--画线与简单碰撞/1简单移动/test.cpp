#include <windows.h>

#define _MAP_W 10
#define _MAP_H 4

int ww,wh;
int x,y;

//HWND g_hWnd;

void UpdateWindowPos(HWND hwnd)
{
	MoveWindow(hwnd,x * ww,y * wh,ww,wh,TRUE);
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
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_UP:
				{
					if(y > 0)
						y--;
					break;
				}
			case VK_DOWN:
				{
					if(y < _MAP_H - 1)
						y++;
					break;
				}
			case VK_LEFT:
				{
					if(x > 0)
						x--;
					break;
				}
			case VK_RIGHT:
				{
					if(x < _MAP_W - 1)
						x++;
					break;
				}
			}
			UpdateWindowPos(hwnd);
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
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"�˰�";
	RegisterClass(&wc);
	
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	ww = sw / _MAP_W;
	wh = sh / _MAP_H;
	x = y = 0;

	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"���ƶ�",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 0,//���ڵ����Ͻ�x����
							 0,//���ڵ����Ͻ�y����
							 200,//���ڵĿ����أ�
							 200,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}