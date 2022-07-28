#include <windows.h>
#include <vector>

#define _MAP_W 800
#define _MAP_H 640

std::vector<RECT> g_vRect;
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
			
			RECT r
				= 
			{
				p.x - 50,
				p.y - 50,
				p.x + 50,
				p.y + 50
			};

			if(p.x - 50 < 0)
				r.left = 0;
			if(p.x + 50 > _MAP_W - 1)
				r.right = _MAP_W - 1;
			if(p.y - 50 < 0)
				r.top = 0;
			if(p.y + 50 > _MAP_H - 1)
				r.bottom = _MAP_H - 1;

			RECT lr;
			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
			{
				if(IntersectRect(&lr,&(*i),&r) == TRUE)
				{
					MessageBoxA(hwnd,"�����ظ�","��ʾ",MB_OK);
					return 0;
				}
			}

			g_vRect.push_back(r);

			InvalidateRect(hwnd,//���ھ��
				          0,//����ľ��ε�ַ��Ϊ0��ʾ�����ͻ���
						  TRUE);//�Ƿ��ò���ϵͳ���ƴ��ڱ���ɫ
							//(����ǣ���WM_PAINT��Ϣ�еĻ��ƻ���ϵͳ�ð�ɫ���
			               //�����ͻ���֮���������WM_PAINT��Ϣ֮ǰ����ϵͳ
							//�����ð�ɫ���ͻ���)
			return 0;
		}
	//case WM_RBUTTONDOWN:
	//	{
	//		//if(g_vPoint.size() > 0)
	//		//{
	//		//	g_vPoint.pop_back();
	//		//	InvalidateRect(hwnd,0,TRUE);
	//		//}
	//		return 0;
	//	}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);


			for(std::vector<RECT>::iterator i = g_vRect.begin(); i != g_vRect.end();++i)
			{
				Rectangle(hdc,i->left,i->top,i->right,i->bottom);
			}
			
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

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	RECT wr =
	{
		(sw - _MAP_W) / 2,
		(sh - _MAP_H) / 2,
		(sw - _MAP_W) / 2 + _MAP_W,
		(sh - _MAP_H) / 2 + _MAP_H
	};
	
	AdjustWindowRect(&wr,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,FALSE	);

	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"�����Ƿ��ظ�",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 wr.left,//���ڵ����Ͻ�x����
							 wr.top,//���ڵ����Ͻ�y����
							 wr.right - wr.left,//���ڵĿ����أ�
							 wr.bottom - wr.top,//���ڵĸߣ����أ�
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