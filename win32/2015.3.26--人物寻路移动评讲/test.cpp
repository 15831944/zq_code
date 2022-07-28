#include <windows.h>
#include <vector>
#include "FindPath.h"
#include "UseBmp.h"

#pragma comment(lib,"MSIMG32.lib")

HDC bmpdc[2];

#define _MAP_W 15
#define _MAP_H 12
#define _MAP_S (_MAP_W * _MAP_H)

#define _TL 0

char map[_MAP_S];

int g_xw;
int g_xh;

bool g_isHeroMove = false;

POINT g_heroPoint = {0,0};

int path[_MAP_S];
int pathlen = 0;

int curpath;//��ǰλ��
int curstep;//��ǰ����
int herox;
int heroy;

int hero_dir = 1;//0123��������

RECT rect;
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
			if(g_isHeroMove)
				return 0;
			int x = LOWORD(lParam) / g_xw;
			int y = HIWORD(lParam) / g_xh;
			bool find = CFindPath::FindPathW(
				map,_MAP_W,_MAP_H,
				g_heroPoint.x + g_heroPoint.y * _MAP_W,
				x + y * _MAP_W,path,&pathlen);
			if(!find)
				return 0;

			g_isHeroMove = true;
			//�õ�Ӣ�۵�ǰ������λ�ú�ͼƬ
			curpath = 0;//��ǰ��·�������е�λ��

			curstep = 0;//��ǰ����

			herox = g_heroPoint.x * g_xw;
			heroy = g_heroPoint.y * g_xh;

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
			if(g_isHeroMove)
			{
				if(curpath == pathlen - 1)
				{
					g_isHeroMove = false;
					return 0;
				}
				//�õ�����
				switch(path[curpath + 1] - path[curpath])
				{
				case -_MAP_W:hero_dir = 0;break;
				case _MAP_W: hero_dir = 1;break;
				case -1:hero_dir = 2;break;
				case 1:hero_dir = 3;break;
				}

				if(curstep == 3)
				{
					curpath += 1;
					curstep = 0;
					g_heroPoint.x = path[curpath] % _MAP_W;
					g_heroPoint.y = path[curpath] / _MAP_W;
				}
				else
				{
					++curstep;

					switch(hero_dir)
					{
					case 0:heroy -= g_xh/3;break;
					case 1:heroy += g_xh/3;break;
					case 2:herox -= g_xw/3;break;
					case 3:herox += g_xw/3;break;
					}
				}

			}
			
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

			bool gaibian = false;

			RECT clientRect ;
			GetClientRect(hwnd,&clientRect);
			if(rect.right - rect.left != clientRect.right - clientRect.left
			|| rect.bottom - rect.top != clientRect.bottom - clientRect.top)
				gaibian = true;
			rect = clientRect;

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

			//����Ӣ��

			if(gaibian)
			{
				herox = g_heroPoint.x * g_xw;
				heroy = g_heroPoint.y * g_xh;
			}
			if(g_isHeroMove)
			{
				TransparentBlt(hdc,herox,heroy,g_xw,g_xh,bmpdc[0],
					curstep * 30,hero_dir * 33,30,33,RGB(0,255,0));
			}
			else
			{

				TransparentBlt(hdc,herox,heroy,g_xw,g_xh,bmpdc[0],
					0,hero_dir * 33,30,33,RGB(0,255,0));
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
	
	GetClientRect(hWnd,&rect);

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