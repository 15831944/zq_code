#include <windows.h>
#include <time.h>
#include "UseBmp.h"
#pragma comment(lib,"msimg32.lib")

BOOL g_Act = TRUE;//���ڼ����־

HDC g_mainDC;//����ʾ�豸
HDC backDC;//���豸

HDC g_bmpdc[2];

#define _MAX_NUM 10000

//���λ����ԭ��
//��ֱ�ӽ��������������豸��,���Ƚ���������һ���󱸵��豸��
//(����һ�������豸),������ٽ������豸�������ɫ����ͨ��BitBlt
//һ���Ի��Ƶ����豸���ͱ�����Ƶ���Ĳ������豸����ȡ�ø��õ�
//����Ч��

void GameInit(HWND hwnd)
{
	//��ȡ����ʾ�豸
	g_mainDC = GetDC(hwnd);

	//�������豸Ϊ����ʾ�豸�ļ����豸
	backDC = CreateCompatibleDC(g_mainDC);
	
	//��Ϊ�����豸����ɫ��ʽ����Ǻڰ׵ģ��ǲ��������豸
	//������ɫ��λ�鴫�䣬����Ҫ
	//����һ����ָ�����豸��ɫ��ʽ��ͬ��λͼ.��Ҫָ����͸�
	HBITMAP hbmp = CreateCompatibleBitmap(g_mainDC,640,480);

	DeleteObject(SelectObject(backDC,hbmp));
	DeleteObject(hbmp);

	g_bmpdc[0] = GetBmpDC(hwnd,"0.bmp");
	g_bmpdc[1] = GetBmpDC(hwnd,"1.bmp");

	srand((unsigned int)time(0));
}

void GameRun()
{
	//�õ�����ѭ���Ŀ�ʼʱ��
	//�õ���������ϵͳһ˲�䵽Ŀǰ�����ĺ�����
	int begintime = GetTickCount();
	//��ָ�����豸���Ϊ��ɫ���߰�ɫ
	BitBlt(backDC,0,0,640,480,0,0,0,WHITENESS);

	//��ͼ���ں���ʾ�豸
	BitBlt(backDC,0,0,640,480,g_bmpdc[0],0,0,SRCCOPY);
	//TransparentBlt(g_mainDC,g_hero.x,g_hero.y,100,100,
	//	g_bmpdc[1],0,0,100,100,RGB(0,255,0));

	for(int i = 0 ; i < _MAX_NUM;++i)
		BitBlt(backDC,rand() % 640,rand() % 480,100,100,g_bmpdc[1],0,0,SRCCOPY);


	//�����豸�����ݴ�������豸
	BitBlt(g_mainDC,0,0,640,480,backDC,0,0,SRCCOPY);

	//һ����˵�����ǻ��ڻ��ƺ󽫺��豸���һ��
	BitBlt(backDC,0,0,640,480,0,0,0,WHITENESS);
	//if(GetAsyncKeyState(VK_UP) & 0x8000)
	//	g_hero.y -= 5;
	//if(GetAsyncKeyState(VK_DOWN) & 0x8000)
	//	g_hero.y += 5;
	//if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	g_hero.x -= 5;
	//if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//	g_hero.x += 5;

	int alltime = GetTickCount() - begintime;
	if(alltime < 33)
		Sleep(33 - alltime);
	else
		Sleep(1);

	Sleep(33);
}

void GameEnd(HWND hwnd)
{
	ReleaseDC(hwnd,g_mainDC); 
	DeleteBmpDC(g_bmpdc[0]);
	DeleteBmpDC(g_bmpdc[1]);
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
							 "���λ���",//���ڱ���������
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