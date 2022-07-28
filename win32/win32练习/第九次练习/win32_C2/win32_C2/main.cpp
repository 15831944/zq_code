#include <windows.h>
#include<vector>
#include"Astar.h"

#pragma comment(lib,"MSIMG32.lib")

#define _CLIENT_W 800
#define _CLIENT_H 600

#define MAP_W 20
#define MAP_H 15
#define MAP_S MAP_W*MAP_H

#define _LEFT 2
#define _RIGHT 3
#define _UP 0
#define _DOWN 1

#define _KD 1
#define _ZA 0



HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImageA(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
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

struct ZA
{
	POINT p;
	int time;
};

char map[MAP_S];

//�ϰ�vector


HDC bmpdc[2];
//ÿ�����ӵĿ�
int ew=_CLIENT_W/MAP_W;
//ÿ�����ӵĸ�
int eh=_CLIENT_H/MAP_H;
//Ӣ��λ��
POINT Hero_p;
//����Ӣ�۷���
int dir;
//�յ�
POINT end_p;
//�Ƿ����ƶ�״̬
bool isMove;
//�ƶ�ʱ��ͼƬ�л�
int pic;
//�Ʋ���
int jbq;
//����ϰ���vector
std::vector<ZA> g_vZa;
//�ƶ�ʱ��·��
int luchang;
//����ƶ�ʱ��·��
int path[MAP_S];
//�ƶ������±��¼
int flag;




//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			/*g_vZa.clear();*/
			for(int i=0;i<MAP_S;i++)
			{
				map[i]=_KD;
			}
			Hero_p.x = 0;
			Hero_p.y = 0;
			dir=_DOWN;
			isMove=false;
			pic=1;
			jbq=1;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			for(int i=0;i<=MAP_H;i++)
			{
				POINT p;
				MoveToEx(hdc,0,i*eh,&p);
				LineTo(hdc,_CLIENT_W-1,i*eh);
			}
			for(int i=0;i<=MAP_W;i++)
			{
				POINT p;
				MoveToEx(hdc,i*ew,0,&p);
				LineTo(hdc,i*ew,_CLIENT_H-1);
			}
			for(std::vector<ZA>::iterator i=g_vZa.begin();i!=g_vZa.end();i++)
			{
				TransparentBlt(hdc,
						i->p.x*ew,
						i->p.y*eh,
						ew,
						eh,
						bmpdc[1],
						30*(i->time),
						0,
						30,
						33,
						RGB(0,255,0));
				if(i->time==7)
				{
					i->time=0;
				}else
				{
					i->time++;
				}
			}
			if(!isMove)
			{
				TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						0,
						33*dir,
						30,
						33,
						RGB(0,255,0));
			}else
			{
				int k = path[flag]-path[flag-1];
				switch(k)
				{
				case MAP_W:
					{
						dir = _UP;
						break;
					}
				case -MAP_W:
					{
						dir = _DOWN;
						break;
					}
				case 1:
					{
						dir = _LEFT;
						break;
					}
				case -1:
					{
						dir = _RIGHT;
						break;
					}
				}
				switch(dir)
				{
				case _RIGHT:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew+jbq*ew/4,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _LEFT:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew-jbq*ew/4,
						Hero_p.y*eh,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _UP:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh-jbq*eh/4,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				case _DOWN:
					{
						TransparentBlt(hdc,
						Hero_p.x*ew,
						Hero_p.y*eh+jbq*eh/4,
						ew,
						eh,
						bmpdc[0],
						30*pic,
						33*dir,
						30,
						33,
						RGB(0,255,0));
						break;
					}
				}
				if(pic==1)
				{
					pic=2;
				}else
				{
					pic=1;
				}
				jbq++;
				if(jbq == 4+1)
				{
					jbq = 1;
					Hero_p.x = path[flag-1]%MAP_W;
					Hero_p.y = path[flag-1]/MAP_W;
					flag --;
					if(flag==0)
					{
						isMove = false;
					}
					InvalidateRect(hwnd,0,TRUE);
				}
				

			}
		
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if(!isMove)
			{
				int x1 = LOWORD(lParam)/ew;
				int y1 = HIWORD(lParam)/eh;
				end_p.x = x1;
				end_p.y = y1;
				if(map[x1 + y1 * MAP_W] != _ZA && ((Hero_p.x + Hero_p.y * MAP_W) != (x1 +y1 * MAP_W)))
				{
					luchang = AStar::FindPath(map,20,15,Hero_p.x + Hero_p.y * MAP_W ,x1 + y1 * MAP_W,path);
					if(luchang>0)
					{
						isMove = true;
						flag = luchang -1;
						InvalidateRect(hwnd,0,TRUE);
					}
				}
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			if(!isMove)
			{
				POINT p = {LOWORD(lParam),HIWORD(lParam)};
				int x1 = p.x/ew;
				int y1 = p.y/eh;
				p.x = x1;
				p.y = y1;
				if(map[x1+y1*MAP_W]==_KD&&((Hero_p.x+Hero_p.y*MAP_W)!=(x1+y1*MAP_W)))
				{
					ZA z ={p,0};
					g_vZa.push_back(z);
					map[x1+y1*MAP_W]=_ZA;
					InvalidateRect(hwnd,0,TRUE);
				}else
				if(map[x1+y1*MAP_W]==_ZA)
				{
					for(std::vector<ZA>::iterator i = g_vZa.begin();i!=g_vZa.end();i++)
					{
						if(i->p.x ==p.x&&i->p.y == p.y)
						{
							g_vZa.erase(i);
							map[x1+y1*MAP_W]=_KD;
							InvalidateRect(hwnd,0,TRUE);
							break;
						}
					}
				}
			}
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
	wc.lpszClassName = L"�˰�";
	RegisterClass(&wc);
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
	
	
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 L"����ƶ�Ӣ�ۡ��Ҽ�����ȡ���ϰ�",//���ڱ���������
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right-r.left,//���ڵĿ����أ�
							 r.bottom-r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
	
	
	bmpdc[0] = GetBmpDC(hWnd,"0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"1.bmp");

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	SetTimer(hWnd,0,60,0);

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