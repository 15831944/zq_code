//#include <windows.h>
//#include <vector>
//
//#define _MAP_W 800
//#define _MAP_H 640
////��ͼ���ܻ����ٸ�
//#define _MAP_W_W 10
//#define _MAP_W_H 8
////��ͼ����
//char map[]=
//{
//	0,1,1,1,1,1,1,1,1,0,
//	0,0,0,1,0,0,0,1,1,0,
//	0,1,0,1,1,1,0,1,1,0,
//	0,1,0,0,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,0,0,0,1,1,0,
//	0,1,1,1,1,1,1,1,1,0
//};
////ÿһ�����η�Χ�����ؿ�͸�
//int ew,eh;
////��¼���еľ���
//std::vector<RECT> g_vRect;
//
////Ӣ�۵ľ���
//RECT ellRect;
//
////Ӣ������
//int x,y;
//
////������Ϣ��������������������ϵͳ����
//__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
//								unsigned int uMsg,//��Ϣ����
//								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
//								__w64 long lParam)//��Ϣ���Ӳ���2
//{
//	switch(uMsg)
//	{
//	case WM_DESTROY:
//		{
//			PostQuitMessage(0);
//			return 0;
//		}
//	case WM_KEYDOWN:
//		{
//			int lx = x;
//			int ly = y;
//			if(wParam == VK_UP)
//			{
//				if(y > 0)
//					y--;
//			}
//			if(wParam == VK_DOWN)
//			{
//				if(y < _MAP_W_H - 1)
//					y++;
//			}
//			if(wParam == VK_LEFT)
//			{
//				if(x > 0)
//					x--;
//			}
//			if(wParam == VK_RIGHT)
//			{
//				if(x < _MAP_W_W - 1)
//					x++;
//			}
//
//			RECT lsr = 
//			{
//				ew * x,
//				eh * y,
//				ew * x + ew,
//				eh * y + eh
//			};
//
//			RECT returnR;
//			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
//			{
//				if(IntersectRect(&returnR,&(*i),&lsr) == TRUE)
//				{
//					x = lx;
//					y = ly;
//					return 0;
//				}
//			}
//
//			ellRect.left = ew * x;
//			ellRect.top = eh * y;
//			ellRect.right = ew * x + ew;
//			ellRect.bottom = eh * y + eh;
//
//			InvalidateRect(hwnd,0,TRUE);
//			return 0;
//		}
//		//InvalidateRect,InvalidateRgn����
//	//case WM_LBUTTONDOWN:
//	//	{
//	//		POINT p = {LOWORD(lParam),HIWORD(lParam)};
//	//		
//	//			if(IntersectRect(&lr,&(*i),&r) == TRUE)
//
//
//	//		InvalidateRect(hwnd,//���ھ��
//	//			          0,//����ľ��ε�ַ��Ϊ0��ʾ�����ͻ���
//	//					  TRUE);//�Ƿ��ò���ϵͳ���ƴ��ڱ���ɫ
//	//						//(����ǣ���WM_PAINT��Ϣ�еĻ��ƻ���ϵͳ�ð�ɫ���
//	//		               //�����ͻ���֮���������WM_PAINT��Ϣ֮ǰ����ϵͳ
//	//						//�����ð�ɫ���ͻ���)
//	//		return 0;
//	//	}
//	case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//			HDC hdc = BeginPaint(hwnd,&ps);
//
//			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
//			{
//				Rectangle(hdc,i->left,i->top,i->right,i->bottom);
//			}
//
//			Ellipse(hdc,ellRect.left,ellRect.top,ellRect.right,ellRect.bottom);
//			char buf[32];
//			sprintf_s(buf,32,"%d,%d",x,y);
//			TextOutA(hdc,ellRect.left,ellRect.top,buf,(int)strlen(buf));
//			EndPaint(hwnd,&ps);
//
//			return 0;
//		}
//	}
//	return DefWindowProc(hwnd,uMsg,wParam,lParam);
//}
//
//int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
//					  HINSTANCE hPrevInstance,
//					  LPSTR lpCmdLine,
//					  int nCmdShow)
//{
//	WNDCLASS wc;
//	wc.style = CS_HREDRAW|CS_VREDRAW;
//	wc.lpfnWndProc = WindowProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	
//	wc.hIcon = LoadIcon(0,IDI_APPLICATION);
//	
//	wc.hCursor = LoadCursor(0,IDC_ARROW);
//	
//	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
//	
//	wc.lpszMenuName = 0;
//	
//	wc.lpszClassName = L"�˰�";
//	
//	RegisterClass(&wc);
//
//	int sw = GetSystemMetrics(SM_CXSCREEN);
//	int sh = GetSystemMetrics(SM_CYSCREEN);
//
//	RECT wr =
//	{
//		(sw - _MAP_W) / 2,
//		(sh - _MAP_H) / 2,
//		(sw - _MAP_W) / 2 + _MAP_W,
//		(sh - _MAP_H) / 2 + _MAP_H
//	};
//	
//	AdjustWindowRect(&wr,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,FALSE	);
//
//	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
//		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
//							 //������ɴ������ڵ�����
//							 L"���ƶ�����ײ",//���ڱ���������
//							 WS_OVERLAPPEDWINDOW,//���ڷ��
//							 wr.left,//���ڵ����Ͻ�x����
//							 wr.top,//���ڵ����Ͻ�y����
//							 wr.right - wr.left,//���ڵĿ����أ�
//							 wr.bottom - wr.top,//���ڵĸߣ����أ�
//							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
//							 0,//���ڲ˵��������ʹ�ò˵���0
//							 wc.hInstance,//Ӧ�ó���ʵ�����
//							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
//
//	RECT clientR;
//	GetClientRect(hWnd,&clientR);
//	int cw = clientR.right - clientR.left;
//	int ch = clientR.bottom - clientR.top;
//
//	ew = cw / _MAP_W_W;
//	eh = ch / _MAP_W_H;
//
//	bool setHero = false;
//	
//	for(int i = 0;i < _MAP_W_H;++i)
//	{
//		for(int j = 0; j < _MAP_W_W;++j)
//		{
//			if(map[j + i * _MAP_W_W] == 1)
//			{
//				RECT jx = 
//				{
//					ew * j,
//					eh * i,
//					ew * j + ew,
//					eh * i + eh
//				};
//				g_vRect.push_back(jx);
//			}
//			else if(!setHero && map[j + i * _MAP_W_W] == 0)
//			{
//				setHero = true;
//				ellRect.left = ew * j;
//				ellRect.top = eh * i;
//				ellRect.right = ew * j + ew;
//				ellRect.bottom = eh * i + eh;
//				x = j;
//				y = i;
//			}
//		}
//	}
//
//
//	ShowWindow(hWnd,nCmdShow);
//	UpdateWindow(hWnd);
//	
//	MSG msg;
//	while(GetMessage(&msg,0,0,0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	return 1;
//}

#include <windows.h>
#include <vector>

#define _MAP_W 10
#define _MAP_H 8
#define _GRID_W 50
#define _GRID_H 60
#define _CLIENT_W (_MAP_W * _GRID_W)
#define _CLIENT_H (_MAP_H * _GRID_H)
int x, y;
char map[]=
{
	1,1,0,1,1,1,1,1,1,1,
	1,1,0,0,1,1,1,1,1,1,
	1,1,1,0,1,1,1,1,1,1,
	1,1,1,0,1,0,0,1,1,1,
	1,1,1,1,1,1,0,0,0,1,
	1,1,1,1,1,1,1,1,0,1,
	1,1,0,0,1,1,1,0,1,1,
	1,1,0,1,1,1,1,1,1,1
};

__w64 long __stdcall WindowProc(HWND hwnd,
								unsigned int uMsg,
								__w64 unsigned int wParam,
								__w64 long lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_KEYDOWN:
		{
			bool ok = true;

			switch (wParam)
			{
			case VK_UP:
				{
					if (y > 0 && map[x + (y - 1) * _MAP_W] == 1)
						--y;
					break;
				}
			case VK_DOWN:
				{
					if (y < _MAP_H - 1 && map[x + (y + 1) * _MAP_W] == 1)
						++y;
					break;
				}
			case VK_LEFT:
				{
					if (x > 0 && map[x - 1 + y * _MAP_W] == 1)
						--x;
					break;
				}
			case VK_RIGHT:
				{
					if (x < _MAP_W - 1 && map[x + 1 + y * _MAP_W] == 1)
						++x;
					break;
				}
			default:
				{
					ok = false;
				}
			}
			if (ok)
				InvalidateRect(hwnd, 0, TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			for (int i = 0; i < _MAP_W * _MAP_H; ++i)
			{
				int cx = i % _MAP_W;
				int cy = i / _MAP_W;
				if (0 == map[cx + cy * _MAP_W])
					Rectangle(hdc, cx * _GRID_W, cy * _GRID_H, (cx + 1) * _GRID_W, (cy + 1) * _GRID_H);
			}
			Ellipse(hdc, x * _GRID_W, y * _GRID_H, (x + 1) * _GRID_W, (y + 1) * _GRID_H);
			char buf[32];
			sprintf_s(buf, 32, "%d-%d", x, y);
			TextOutA(hdc, x * _GRID_W, y * _GRID_H, buf, (int)strlen(buf));
			
			EndPaint(hwnd, &ps);
			return 0;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"����";

	RegisterClass(&wc);
	HWND hWnd = CreateWindow(
				wc.lpszClassName,
				L"���ƶ�����ײ",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				HWND_DESKTOP,
				0,
				wc.hInstance,
				0);
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}