#include <windows.h>
#include <vector>
#include "resource.h"
#include "GameLogic.h"

//CGameLogic : ��Ϸ�߼���
//CPlane:�ɻ����� OK
//CEmenyPlane : public CPlane ���˷ɻ��࣬�̳���CPlane OK
//CHeroPlane:public CPlane c�ɻ��࣬�̳���CPlane OK
//CBullet �ӵ����� OK
//CEmenyBullet:public CBullet �����ӵ��� ���̳���CBullet OK
//CHeroBullet:public CBullet Ӣ���ӵ��� ���̳���CBullet OK
//CGameOutput ����࣬��Ҫ������ƻ���

CGameLogic g_clogic;

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
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == 0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						DestroyWindow(hwnd);
					}
					break;
				case ID_40002:
					{
						SetTimer(hwnd,0,100,0);
					}
					break;
				case ID_40003:
					{
						SetTimer(hwnd,0,60,0);
					}
					break;
				case ID_40004:
					{
						SetTimer(hwnd,0,20,0);
					}
					break;
				}
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT point = {LOWORD(lParam),HIWORD(lParam)};
			g_clogic.SetHeroAttack(point);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			g_clogic.Brom();
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			POINT point = {LOWORD(lParam),HIWORD(lParam)};
			g_clogic.SetHeroPoint(point);
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_TIMER:
		{
			g_clogic.Run();
			InvalidateRect(hwnd,0,TRUE);
			return 0;
		}
	case WM_PAINT:
		{
			g_clogic.Paint(hwnd);
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
	//���ڽṹ����������б����������ṹ�崴�����Ĵ��ڶ����У�
	//CS_HREDRAW : ����ˮƽ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	//CS_VREDRAW : ������ֱ�ߴ緢���ı�ͻ��ػ�(Ͷ��WM_PAINT��Ϣ)
	wc.style = CS_HREDRAW|CS_VREDRAW;
	//������Ϣ�����ĵ�ַ
	wc.lpfnWndProc = WindowProc;
	//�������Ķ����ֽڣ�һ�㲻ʹ��
	wc.cbClsExtra = 0;
	//���ڵĶ����ֽڣ�һ�㲻ʹ��
	wc.cbWndExtra = 0;
	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;
	//ͼ��
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//���
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH ��ˢ
	//����ϵͳ���ڻ��ƴ��ڱ����ı�����ˢ
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	//���ڵ�����
	wc.lpszClassName = "�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	
	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "�ɻ�",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0
	
	RECT clientRect;
	GetClientRect(hWnd,&clientRect);
	g_clogic.Init(0,clientRect.right,clientRect.bottom);
	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
	UpdateWindow(hWnd);
	
	SetTimer(hWnd,0,30,0);
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR�� Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}

	KillTimer(hWnd,0);

	return 1;
}