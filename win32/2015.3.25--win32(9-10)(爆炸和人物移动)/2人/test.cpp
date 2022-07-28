#include <windows.h>
#include <vector>

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

#define _MAP_W 15
#define _MAP_H 12
#define _MAP_S (_MAP_W * _MAP_H)

#define _TL 0

char map[_MAP_S];

int g_xw;
int g_xh;

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
			

			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam) / g_xw;
			int y = HIWORD(lParam) / g_xh;

			if(map[x + y * _MAP_W] == _TL)
				map[x + y * _MAP_W] = 1;
			else 
				map[x + y * _MAP_W] = _TL;
			return 0;
		}
	case WM_TIMER:
		{
			
			for(int i = 0; i < _MAP_S;++i)
			{
				if(map[i] != _TL)
				{
					if(map[i] == 8)
						map[i] = 1;
					else
						map[i] += 1;
				}
			}
			
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			RECT clientRect ;
			GetClientRect(hwnd,&clientRect);

			int cw = clientRect.right - clientRect.left;
			int ch = clientRect.bottom - clientRect.top;

			//Rectangle(hdc,0,0,clientRect.right,clientRect.bottom);
			g_xw = cw / _MAP_W;
			g_xh = ch / _MAP_H;

			for(int i = 1; i < _MAP_H; ++i)
			{
				POINT p;
				MoveToEx(hdc,0,i * g_xh,&p);
				LineTo(hdc,cw,g_xh * i);
			}
			for(int i = 1; i < _MAP_W; ++i)
			{
				POINT p;
				MoveToEx(hdc,i * g_xw,0,&p);
				LineTo(hdc,g_xw * i,ch);
			}

			for(int i = 0 ; i < _MAP_S; ++i)
			{
				if(map[i] != _TL)
				{
					int x = (i % _MAP_W) * g_xw;
					int y = (i / _MAP_W) * g_xh;
					TransparentBlt(hdc,x,y,g_xw,g_xh,bmpdc[1],(map[i] - 1)* 30,0,30,33,RGB(0,255,0));
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
							 "��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	bmpdc[0] = GetBmpDC(hWnd,"bmp\\0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"bmp\\1.bmp");
	
	for(int i = 0; i < _MAP_S;++i)
		map[i] = _TL;

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
	DeleteBmpDC(bmpdc[0]);
	DeleteBmpDC(bmpdc[1]);

	return 1;
}