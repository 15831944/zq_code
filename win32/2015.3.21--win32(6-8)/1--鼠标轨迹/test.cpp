#include <windows.h>
#include <list>



std::list<POINT> g_lPointList;

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
	case WM_MOUSEMOVE:
		{
			if(g_lPointList.size() < 32)
			{
				POINT p = {LOWORD(lParam),HIWORD(lParam)};
				g_lPointList.push_back(p);
			}
			return 0;
		}
	case WM_TIMER:
		{
			if(g_lPointList.size() > 0)
				g_lPointList.pop_front();

			InvalidateRect(hwnd,0,1);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			if(g_lPointList.size() > 1)
			{
				int add_c = 255 / (g_lPointList.size() - 1);
				std::list<POINT>::iterator i = g_lPointList.begin();
				int init_c = 255;
				for(++i; i != g_lPointList.end(); ++i)
				{
					std::list<POINT>::iterator j = i;
					--j;
					init_c -= add_c;

					HPEN p1 = CreatePen(PS_SOLID,1,RGB(init_c,init_c,init_c));
					HPEN p2 = (HPEN)SelectObject(hdc,p1);

					POINT q;
					MoveToEx(hdc,j->x,j->y,&q);
					LineTo(hdc,i->x,i->y);

					SelectObject(hdc,p2);
					DeleteObject(p1);
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
							 "���켣",//���ڱ���������
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

	return 1;
}