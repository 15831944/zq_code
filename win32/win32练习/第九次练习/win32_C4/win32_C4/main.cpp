#include <windows.h>
#include"UseBmp.h"
#include<iostream>

#pragma comment(lib,"MSIMG32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480

#define _XDL 5   //�ж���

//�����豸
HDC bmpdc; 
//�ͻ�����С
RECT client_r;
//Ӣ�۾���
RECT hero_r={220,290,240,320};

__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	//������Ϣ������ʽ
	//1)���ϵͳ�˵��Ĺرղ˵��Alt + F4��
	//2)���Ͻǵ�X��ť
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			GetClientRect(hwnd,&client_r);

			TransparentBlt(hdc,client_r.left,client_r.top,client_r.right,client_r.bottom,
						   bmpdc,0,0,640,480,RGB(0,0,0));
			Rectangle(hdc,hero_r.left,hero_r.top,hero_r.right,hero_r.bottom);

			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT p ={LOWORD(lParam),HIWORD(lParam)};
			char buf[256];
			HDC hdc = GetDC(hwnd);
			COLORREF color = GetPixel(hdc,p.x,p.y);
			unsigned char r =  GetRValue(color);
			unsigned char g =  GetGValue(color);
			unsigned char b =  GetBValue(color);
			sprintf_s(buf,256,"R:%d,G:%d,B:%d",r,g,b);
			MessageBoxA(hwnd,buf,"��ʾ",MB_OK);
			ReleaseDC(hwnd,hdc);
			return 0;
		}
	case WM_KEYDOWN:
		{
			HDC hdc = GetDC(hwnd);
			COLORREF color;
			//��
			if(wParam == VK_UP)
			{
				RECT r ={ hero_r.left,hero_r.top-_XDL,hero_r.right,hero_r.top};
				int flag = 0;
				for(int i = r.left;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.top-=_XDL;
					hero_r.bottom-=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//��
			if(wParam == VK_DOWN)
			{
				RECT r ={ hero_r.left,hero_r.bottom,hero_r.right,hero_r.bottom+_XDL};
				int flag = 0;
				for(int i = r.left;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top+1;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.top+=_XDL;
					hero_r.bottom+=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//��
			if(wParam == VK_LEFT)
			{
				RECT r ={ hero_r.left-_XDL,hero_r.top,hero_r.left,hero_r.bottom};
				int flag = 0;
				for(int i = r.left;i<r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.left-=_XDL;
					hero_r.right-=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			//��
			if(wParam == VK_RIGHT)
			{
				RECT r ={ hero_r.right-_XDL,hero_r.top,hero_r.right+_XDL,hero_r.bottom};
				int flag = 0;
				for(int i = r.left+1;i<=r.right;i++)
				{
					int flag1=0;
					for(int j =r.top;j<=r.bottom;j++)
					{
						color = GetPixel(hdc,i,j);
						if(color==RGB(128,64,0))
						{
							flag =1;
							flag1 =1;
							break;
						}
					}
					if(flag1==1)
						break;
				}
				if(flag == 0)
				{
					hero_r.left+=_XDL;
					hero_r.right+=_XDL;
					InvalidateRect(hwnd,0,TRUE);
				}
			}
			ReleaseDC(hwnd,hdc);
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;

	wc.hCursor = 0;

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wc.lpszMenuName = 0;

	wc.lpszClassName = L"�˰�";

	RegisterClass(&wc);

	//�õ���ǰ����Ŀ�͸�
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	//���ڵ�λ�ã���С
	RECT r = 
	{
		(sw - _CLIENT_W)/2,
		(sh - _CLIENT_H)/2,
		(sw - _CLIENT_W)/2 + _CLIENT_W,
		(sh - _CLIENT_H)/2 + _CLIENT_H
	};

	AdjustWindowRect(&r,//�趨�Ŀͻ�����λ�ã����
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//���ڷ��
	FALSE);//�Ƿ��в˵�

	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"������ײ",//���ڱ���������
							 //WS_THICKFRAME ͨ������϶��ı䴰�ڴ�С
							 //WS_MAXIMIZEBOX �������Ͻǵ���󻯺ͻ�ԭ��ť
							 WS_OVERLAPPEDWINDOW ,//& ~WS_THICKFRAME ,//& ~WS_MAXIMIZEBOX,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	bmpdc = GetBmpDC(hWnd,"0.bmp");

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);


	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteDC(bmpdc);

	return 1;
}


