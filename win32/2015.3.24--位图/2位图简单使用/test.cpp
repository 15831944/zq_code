#include <windows.h>
#include "resource.h"


HBITMAP hbmp[2];
HBITMAP hbmp1[2];

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
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			//�������ݵ��豸DC
			HDC bmpdc[4];
			bmpdc[0] = CreateCompatibleDC(hdc);
			bmpdc[1] = CreateCompatibleDC(hdc);
			bmpdc[2] = CreateCompatibleDC(hdc);
			bmpdc[3] = CreateCompatibleDC(hdc);
			
		
			//��BITMAPѡ�뵽�����豸�в���ȡ�ϵ�λͼ
			HBITMAP oldhbmp[4];
			oldhbmp[0] = (HBITMAP)SelectObject(bmpdc[0],hbmp[0]);
			oldhbmp[1] = (HBITMAP)SelectObject(bmpdc[1],hbmp[1]);
			oldhbmp[2] = (HBITMAP)SelectObject(bmpdc[2],hbmp1[0]);
			oldhbmp[3] = (HBITMAP)SelectObject(bmpdc[3],hbmp1[1]);

			//λͼ����
			BitBlt(
				hdc,//Ŀ���豸
				0,//Ŀ��������Ͻ�x����
				0,//Ŀ��������Ͻ�y����
				640,//Ŀ����εĿ�͸�
				480,
				bmpdc[0],//Դ�豸
				0,//Դ�������Ͻǵ�x,y����
				0,
				SRCCOPY);//SRCCOPY��ʾԭ�ⲻ���Ŀ���
	
			BitBlt(hdc,100,50,75,100,bmpdc[1],75,0,SRCCOPY);

			BitBlt(hdc,100,250,75,100,bmpdc[1],75,0,SRCCOPY);
			BitBlt(hdc,300,250,150,100,bmpdc[1],0,0,SRCCOPY);

			BitBlt(hdc,100,250,75,100,bmpdc[2],0,0,SRCCOPY);
			BitBlt(hdc,300,250,150,100,bmpdc[3],0,0,SRCCOPY);

			SelectObject(bmpdc[0],oldhbmp[0]);
			SelectObject(bmpdc[1],oldhbmp[1]);
			SelectObject(bmpdc[2],oldhbmp[2]);
			SelectObject(bmpdc[3],oldhbmp[3]);

			DeleteDC(bmpdc[0]);
			DeleteDC(bmpdc[1]);
			DeleteDC(bmpdc[2]);
			DeleteDC(bmpdc[3]);
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
	hbmp[0] = (HBITMAP)LoadImage(
		0,//���ʹ����Դ�е�λͼ�˴α�����дӦ�ó���ʵ�������������0����
		"1.bmp",//λͼ�ļ�������
		IMAGE_BITMAP,//����
		0,//ϣ�����ص�λͼ�Ŀ�(���ؿ�),Ϊ0���ʾx����ȫ������
		0,//ϣ�����ص�λͼ�ĸ�(���ظ�),Ϊ0���ʾy����ȫ������
		LR_LOADFROMFILE);//LR_LOADFROMFILE��ʾ���ⲿ�ļ�����

	hbmp[1] = (HBITMAP)LoadImage(
		0,//���ʹ����Դ�е�λͼ�˴α�����дӦ�ó���ʵ�������������0����
		"2.bmp",//λͼ�ļ�������
		IMAGE_BITMAP,//����
		0,//ϣ�����ص�λͼ�Ŀ�(���ؿ�),Ϊ0���ʾx����ȫ������
		0,//ϣ�����ص�λͼ�ĸ�(���ظ�),Ϊ0���ʾy����ȫ������
		LR_LOADFROMFILE);//LR_LOADFROMFILE��ʾ���ⲿ�ļ�����

	hbmp1[0] = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,0);
	hbmp1[1] = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP,0,0,0);
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
							 "λͼ��ʹ��",//���ڱ���������
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
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}

	DeleteObject(hbmp[1]);
	DeleteObject(hbmp[0]);

	DeleteObject(hbmp1[1]);
	DeleteObject(hbmp1[0]);
	return 1;
}