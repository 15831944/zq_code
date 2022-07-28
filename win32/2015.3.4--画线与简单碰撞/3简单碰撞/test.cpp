#include <windows.h>

RECT r = {100,200,200,400};

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
		//InvalidateRect,InvalidateRgn����
	case WM_LBUTTONDOWN:
		{
			POINT p = {LOWORD(lParam),HIWORD(lParam)};
			
			//if(p.x >= r.left && p.x <= r.right 
			//&& p.y >= r.top && p.y <= r.bottom)
			//	MessageBoxA(hwnd,"������",0,0);

			//�ж�һ�����Ƿ���һ��������
			if(PtInRect(&r,p))
				MessageBoxA(hwnd,"������",0,0);

			//lprcSrc1��lprcSrc2����ཻ������
			//��lprcDst���Ϊ����
			//lprcSrc1��lprcSrc2������ཻ���ؼ�
			//IntersectRect(
			//	LPRECT lprcDst,//���ε�ַ
			//	CONST RECT *lprcSrc1,//���ε�ַ1
			//	CONST RECT *lprcSrc2);//���ε�ַ2
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			Rectangle(hdc,r.left,r.top,r.right,r.bottom);
			
			EndPaint(hwnd,&ps);

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
	
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"����ײ",//���ڱ���������
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
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//WM_PAINT��������
//���ƽṹ��
//PAINTSTRUCT ps;
//HDC:��ʾ�豸���
//BeginPaint:��ȡָ���Ĵ��ڵĿͻ�������ʾ�豸
//EndPaint:�ͷŻ�ȡ��ָ���Ĵ��ڵĿͻ�������ʾ�豸
//ֻ����WM_PAINT��ʹ��
//GetDC ReleaseDC

//POINT p;
//MoveToEx;
//LineTo
//Rectangle
//Ellipse
//TextOut
//PtInRect
//IntersectRect
