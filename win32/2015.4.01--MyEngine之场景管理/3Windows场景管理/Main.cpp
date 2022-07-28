#include <windows.h>
#include "GameOutput.h"
#include "GameInput.h"

HWND g_hWnd;
BOOL g_Act = TRUE;
CGameOutput* go;
CGameInput* gi;

void GameInit()
{
	go = new CGameOutput(g_hWnd);
	gi = new CGameInput(g_hWnd);
	go->LoadBmp("0.bmp");
	go->LoadFont("0",20,20);
}

void GameRun()
{
	
	go->Begin();
	go->DrawLine(0,0,100,200);
	go->DrawLine(100,0,0,200,RGB(255,0,0));
	go->DrawLine(0,100,100,100,RGB(255,0,255),5);
	go->DrawRectangle1(220,220,280,280,RGB(0,255,0));
	go->DrawRectangle2(250,0,400,50,RGB(0,255,255),RGB(255,255,0));
	go->DrawEllipse1(0,0,300,400,RGB(0,0,255));
	go->DrawEllipse2(150,150,250,250,RGB(255,0,255),RGB(0,255,0));

	go->DrawBmp2("0.bmp",440,150,30,20,0,0);
	go->DrawBmp1("0.bmp",400,100,30,20,0,0,3);
	
	
	go->DrawString1("0",400,400,"����",RGB(0,0,255));
	go->DrawString2("0",100,100,50,50,"����",RGB(0,0,255));
	go->End();

	gi->Run();
	if(gi->Get(_GI_K_UP) == _KS_DH)
	{
		
	}
	if(gi->Get(_GI_M_L) == _KS_DC)
	{}

	int cx,cy;
	if(gi->GetCursor(&cx,&cy))
	{
		
	}
	Sleep(33);
}

void GameEnd()
{
	delete gi;
	delete go;
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
	g_hWnd = CreateWindow(wc.lpszClassName,
							 "�������",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(g_hWnd,nCmdShow);
	UpdateWindow(g_hWnd);
	GameInit();
	MSG msg = {};
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if(g_Act)
		{
			GameRun();
		}
		else
		{
			WaitMessage();
		}
	}

	GameEnd();
	return 1;
}