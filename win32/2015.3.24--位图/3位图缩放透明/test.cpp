#include <windows.h>

#pragma comment(lib,"MSIMG32.lib")

HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImage(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	//��������ʾ�豸
	//HDC maindc = GetDC(HWND_DESKTOP);
	//�õ����豸
	HDC maindc = GetDC(hwnd);

	//����������ʾ�豸
	HDC bmpdc = CreateCompatibleDC(maindc);

	//����λͼѡ������豸��
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	//ɾ����λͼ����λͼѡ�뵽�����豸�󣬼����豸�ڲ���������
	//������һ����λͼ������
	DeleteObject(hbmp);

	//ɾ����λͼ
	DeleteObject(oldbmp);

	//�ͷ����豸
	ReleaseDC(hwnd,maindc);

	return bmpdc;
}

void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}

HDC bmpdc[2];
int x,y;

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
	case WM_LBUTTONDOWN:
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,640,480,bmpdc[0],0,0,SRCCOPY);

			//͸��
			TransparentBlt(
				hdc,//Ŀ���豸
				x - 75,//Ŀ�����
				y - 50,
				150,
				100,
				bmpdc[1],//Դ�豸
				0,//Դ����
				0,
				150,
				100,
				RGB(0,255,0));//Ҫ͸������ɫ

			//����λ�鴫��
			StretchBlt(
				hdc,//Ŀ���豸
				0,0,50,50,//Ŀ�����
				bmpdc[1],//Դ�豸
				0,0,150,100,//Դ����
				SRCCOPY);

			
			StretchBlt(hdc,50,0,50,50,bmpdc[1],0,0,150,100,SRCCOPY);
			//���Ҿ���
			StretchBlt(hdc,0 + 100,200,-100,100,bmpdc[1],0,0,150,100,SRCCOPY);
			//���¾���
			StretchBlt(hdc,200,200 + 100,100,-100,bmpdc[1],0,0,150,100,SRCCOPY);

			//�������Ҿ���
			StretchBlt(hdc,300 + 100,200 + 100,-100,-100,bmpdc[1],0,0,150,100,SRCCOPY);
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
							 "λͼʹ��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0


	bmpdc[0] = GetBmpDC(hWnd,"1.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"2.bmp");

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

	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);

	return 1;
}