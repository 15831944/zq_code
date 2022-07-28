#include <windows.h>
#pragma comment(lib,"msimg32.lib")

HBITMAP hbmp[2];

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
	case WM_TIMER:
		{
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			HDC bmpdc[2];
			bmpdc[0] = CreateCompatibleDC(hdc);
			bmpdc[1] = CreateCompatibleDC(hdc);

			HBITMAP oldbmp[2];
			oldbmp[0] = (HBITMAP)SelectObject(bmpdc[0],hbmp[0]);
			oldbmp[1] = (HBITMAP)SelectObject(bmpdc[1],hbmp[1]);

			BitBlt(hdc,0,0,640,480,bmpdc[0],0,0,SRCCOPY);

			static unsigned char x = 0;
			x += 5;

			//Alpha���
			BLENDFUNCTION bf;
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = x;//0��ȫ͸����255��ȫ��͸��
			bf.AlphaFormat = 0;

			AlphaBlend(hdc,100,50,150,100,bmpdc[1],0,0,150,100,bf);

			BitBlt(hdc,300,250,150,100,bmpdc[1],0,0,SRCCOPY);

			SelectObject(bmpdc[0],oldbmp[0]);
			SelectObject(bmpdc[1],oldbmp[1]);

			DeleteDC(bmpdc[0]);
			DeleteDC(bmpdc[1]);

			EndPaint(hwnd,&ps);
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
	hbmp[0] = (HBITMAP)LoadImage(0,"0.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	hbmp[1] = (HBITMAP)LoadImage(0,"1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
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
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 "��һ�����ڳ���",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	SetTimer(hWnd,0,40,0);
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}
	KillTimer(hWnd,0);

	DeleteObject(hbmp[0]);
	DeleteObject(hbmp[1]);

	return 1;
}