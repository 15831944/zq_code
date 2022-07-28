#include <windows.h>
#include<vector>

#pragma comment(lib,"MSIMG32.lib")

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

struct boom
{
	POINT p;
	int time;
	int PictureChange;
};

HDC bmpdc[2];

std::vector<boom> g_vBoom;



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
			POINT p;
			p.x = LOWORD(lParam);
			p.y = HIWORD(lParam);
			boom b = {p,50,0};
			g_vBoom.push_back(b);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);

			BitBlt(hdc,0,0,640,480,bmpdc[0],0,0,SRCCOPY);

			SetTextColor(hdc,RGB(255,0,0));
			SetBkMode(hdc,TRANSPARENT);

			//͸��
			for(std::vector<boom>::iterator i =g_vBoom.begin();i!=g_vBoom.end();)
			{
				if(i->time!=0)
				{
					char buf[256];
					sprintf_s(buf,256,"%d",i->time);
					TextOutA(hdc,i->p.x,i->p.y,buf,strlen(buf));
				}else
				{
					TransparentBlt(
						hdc,//Ŀ���豸
						i->p.x,//Ŀ�����
						i->p.y,
						54,
						54,
						bmpdc[1],//Դ�豸
						i->PictureChange*54,//Դ����
						0,
						54,
						54,
						RGB(0,255,0));//Ҫ͸������ɫ
				}
				if(i->PictureChange==9)
				{
					i=g_vBoom.erase(i);
				}else
					i++;
			}
			
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_TIMER:
		{
			for(std::vector<boom>::iterator i =g_vBoom.begin();i!=g_vBoom.end();i++)
			{
				if(i->time!=0)
				{
					i->time--;
				}else
				{
					i->PictureChange++;
				}
			}
			InvalidateRect(hwnd,0,TRUE);
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
	//RECT r1={300,300,400,500};
	//AdjustWindowRect(&r1,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,//���ڷ��
	//FALSE);
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 L"λͼʹ��",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 400,//���ڵ����Ͻ�x����
							 200,//���ڵ����Ͻ�y����
							 640,//���ڵĿ����أ�
							 460,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0


	bmpdc[0] = GetBmpDC(hWnd,"0.bmp");
	bmpdc[1] = GetBmpDC(hWnd,"1.bmp");

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