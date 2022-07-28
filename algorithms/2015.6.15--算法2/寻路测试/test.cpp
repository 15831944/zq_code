#include <windows.h>
#include <time.h>
#include "FindPath.h"
#pragma comment(lib,"msimg32.lib")

#define _GRID_W 4 // ͼƬ���
#define _GRID_H 4
#define _MAP_W 200 //��ͼ����Ŀ�
#define _MAP_H 150
#define _MAP_S (_MAP_W * _MAP_H)
#define _CLIENT_W (_GRID_W * _MAP_W)
#define _CLIENT_H (_GRID_H * _MAP_H)
#define _ZA_NUM (_MAP_S / 30)

//��ͼ
char map[_MAP_S] = {};

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
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam), HIWORD(lParam)};
			p.x /= _GRID_W;
			p.y /= _GRID_H;

			std::vector<int> path;

			//int t0 = GetTickCount();
			//FindPathW(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			//int t1 = GetTickCount() - t0;

			//int t2 = GetTickCount();
			//FindPathD(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			//int t3 = GetTickCount() - t2;

			int t4 = GetTickCount();
			FindPathA(map, _MAP_W, _MAP_H, 0, p.x + p.y * _MAP_W, &path);
			int t5 = GetTickCount() - t4;

			//char buf[256];
			//sprintf_s(buf, "��ȣ�%d ��ȣ�%d A�ǣ�%d", t1, t3, t5);
			//SetWindowTextA(hwnd, buf);

			//char buf[256];
			//sprintf_s(buf, "��ȣ�%d A�ǣ�%d", t1, t5);
			//SetWindowTextA(hwnd, buf);

			for (int i = 0; i < path.size(); ++i)
				map[path[i]] = 2;
			
			char buf[256];
			sprintf_s(buf, "A�ǣ�%d", t5);
			SetWindowTextA(hwnd, buf);

			::InvalidateRect(hwnd, 0, TRUE);

			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			for (int i = 0; i < _MAP_S; ++i)
			{
				if (map[i] == 0)
				{
					int x = i % _MAP_W, y = i / _MAP_W;
					x *= _GRID_W;
					y *= _GRID_H;
					Rectangle(hdc, x, y, x + _GRID_W, y + _GRID_H);
				}
				else if (map[i] == 2)
				{
					int x = i % _MAP_W, y = i / _MAP_W;
					x *= _GRID_W;
					y *= _GRID_H;
					SetPixel(hdc, x, y, RGB(255, 0, 0));
				}
			}
			
			EndPaint(hwnd,&ps);
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
	srand((unsigned int)time(0));

	//��ʼ����ͼ
	for (int i = 0; i < _MAP_S; ++i)
		map[i] = 1;
	for (int i = 0; i < _ZA_NUM; ++i)
		map[(rand() * rand()) % _MAP_S] = 0;

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
	wc.lpszClassName = "�Ű�";
	RegisterClass(&wc);
	//��ȡ����Ŀ�
	int sw = GetSystemMetrics(SM_CXSCREEN);
	//��ȡ����ĸ�
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT r = 
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};

	//������ִ����ϣ��Ὣ��һ������ִ�е�RECT����Ϊ����Ӧ�еľ���
	AdjustWindowRect(&r,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
		FALSE);//�Ƿ��в˵�

	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}
	return 1;
}