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
struct _SHIJIAN
{
	POINT p;
	int f;//֡
};
struct _BAOZHA
{
	POINT p;
	int f;
};

std::vector<_SHIJIAN> g_sj;
std::vector<_BAOZHA> g_baozha;

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
			_SHIJIAN shijian = {{LOWORD(lParam),HIWORD(lParam)},50};

			g_sj.push_back(shijian);

			return 0;
		}
	case WM_TIMER:
		{
			for(std::vector<_SHIJIAN>::iterator i = g_sj.begin();i != g_sj.end();)
			{
				if(i->f > 0)
				{
					i->f -=1;
					++i;
				}
				else
				{
					_BAOZHA baozha = {{i->p.x,i->p.y},0};
					g_baozha.push_back(baozha);
					i = g_sj.erase(i);
				}
			}

			for(std::vector<_BAOZHA>::iterator i = g_baozha.begin();i != g_baozha.end();)
			{
				if(i->f < 10)
				{
					i->f +=1;
					++i;
				}
				else
				{
					i = g_baozha.erase(i);
				}
			}
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			//���ݿͻ����ı仯���Ʊ���ͼƬ
			RECT clientRect;
			GetClientRect(hwnd,&clientRect);
			StretchBlt(hdc,clientRect.left,clientRect.top,clientRect.right - clientRect.left,clientRect.bottom - clientRect.top,bmpdc[0],0,0,640,480,SRCCOPY);

			for(std::vector<_BAOZHA>::iterator i = g_baozha.begin();i != g_baozha.end();++i)
			{
				TransparentBlt(hdc,i->p.x,i->p.y,54,54,bmpdc[1],i->f * 54,0,54,54,RGB(0,0,0));
			}

			SetBkMode(hdc,TRANSPARENT);

			for(std::vector<_SHIJIAN>::iterator i = g_sj.begin();i != g_sj.end();++i)
			{
				char buf[32];
				sprintf_s(buf,32,"%d",i->f);
				TextOutA(hdc,i->p.x,i->p.y,buf,(int)strlen(buf));
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
							 "ը��",//���ڱ���������
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