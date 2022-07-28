#include <windows.h>
#include"resource.h"
#include<iostream>

#define _CLIENT_W 640    //�ͻ����Ŀ�
#define _CLIENT_H 480	 //�ͻ����ĸ�

#define _TL 0		//ͨ·
#define _ZA 1		//�ϰ�
#define _HERO 2     //Ӣ��
#define _XZ 3		//����
#define _AIM 4      //Ŀ��
#define _H_AIM 5	//Ӣ��Ŀ��
#define _X_AIM 6    //����Ŀ��

#define MAP_W 10             //��ͼ�Ŀ�
#define MAP_H 10			 //��ͼ�ĸ�
#define MAP_S MAP_W*MAP_H    //��ͼ�ܴ�С

#define EW 25
#define EH 25

#define _TL_C        RGB(255,255,255)			//ͨ·����ɫ
#define _ZA_C 		 RGB(192,192,192)			//�ϰ�����ɫ
#define _HERO_C 	 RGB(255,0,0)				//Ӣ�۵���ɫ
#define _XZ_C 		 RGB(0,255,0)				//���ӵ���ɫ
#define _AIM_C 		 RGB(0,0,255)				//Ŀ�����ɫ
#define _H_AIM_C 	 RGB(138,43,226)			//Ӣ��Ŀ�����ɫ
#define _X_AIM_C 	 RGB(0,245,255)				//����Ŀ�����ɫ


//��ǰѡ��Ĺ�������
int Current_Mouse;
//�Զ����ͼ
char map[MAP_S];
//�Զ����ַ���
const char* c[] ={"ͨ·","�ϰ�","Ӣ��","����","Ŀ��","Ӣ��Ŀ��","����Ŀ��"};

__w64 long __stdcall WindowProc(HWND hwnd,
								unsigned int uMsg,
								__w64 unsigned int wParam,
								__w64 long lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			for(int i=0;i<MAP_S;i++)
			{
				map[i]=_TL;
			}
			Current_Mouse = _TL;
			return 0;
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam)==0)
			{
				switch(LOWORD(wParam))
				{
				case ID_40001:
					{
						for(int i=0;i<MAP_S;i++)
						{
							map[i]=_TL;
							InvalidateRect(hwnd,0,TRUE);
						}
						break;
					}
				case ID_40002:
					{
						char buf[MAX_PATH]	= {};
						OPENFILENAME ofn = {};
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFile = buf;
						ofn.nMaxFile = MAX_PATH;
						if(IDOK == GetOpenFileName(&ofn))
						{
							FILE* pf = 0;
							fopen_s(&pf,buf,"rb");
							int a;
							fread(&a,1,4,pf);
							if(a!=110)
							{
								MessageBoxA(hwnd,"�ļ����ͷǷ�","��ʾ",MB_OK);
							}else
							{
								for(int i=0;i<MAP_S;i++)
								{
									fread(&map[i],1,1,pf);
								}
								MessageBoxA(hwnd,"�򿪳ɹ�","��ʾ",MB_OK);
								InvalidateRect(hwnd,0,1);
							}
							fclose(pf);
						}
						break;
					}
				case ID_40003:
					{
						int num_yx = 0;
						int num_xiangzi = 0;
						int num_mubiao =0;
						//������ͼ����ȡӢ�ۡ����ӡ���Ŀ�������
						for(int i=0;i<MAP_S;i++)
						{
							if(map[i]==_HERO||map[i]==_H_AIM)
							{
								num_yx++;
							}
							if(map[i]==_XZ||map[i]==_X_AIM)
							{
								num_xiangzi++;
							}
							if(map[i]==_AIM||map[i]==_H_AIM||map[i]==_X_AIM)
							{
								num_mubiao++;
							}
						}
						//�жϹؿ��Ƿ�����߼�
						if(num_yx==1&&(num_xiangzi==num_mubiao)&&num_xiangzi!=0)
						{
							char buf[MAX_PATH]	= {};
							OPENFILENAME ofn = {};
							ofn.lStructSize = sizeof(ofn);
							ofn.hwndOwner = hwnd;
							ofn.lpstrFile = buf;
							ofn.nMaxFile = MAX_PATH;
							if(IDOK == GetSaveFileName(&ofn))
							{
								int a =110;
								FILE* pf = 0;
								fopen_s(&pf,buf,"wb");
								fwrite(&a,1,4,pf);
								fwrite(map,1,MAP_S,pf);
								fclose(pf);
								MessageBoxA(hwnd,"����ɹ�","��ʾ",MB_OK);
							}
						}else
						{
							MessageBoxA(hwnd,"�ؿ��Ƿ�,�����ܱ���","��ʾ",MB_OK);
						}
						break;
					}
				case ID_40004:
					{
						DestroyWindow(hwnd);
						break;
					}
				}
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			if( LOWORD(lParam)>=100 
				&& LOWORD(lParam)<=100+MAP_W*EW 
				&& HIWORD(lParam)>=100
				&& HIWORD(lParam)<=350+MAP_H*EH )
			{
				int x =  (LOWORD(lParam)-100)/EW;
				int y =  (HIWORD(lParam)-100)/EH;
				map[x+y*MAP_W] = Current_Mouse;
				InvalidateRect(hwnd,0,TRUE);
			}
			if( LOWORD(lParam)>=400 
				&& LOWORD(lParam)<=480 
				&& HIWORD(lParam)>=100
				&& HIWORD(lParam)<=100+7*EH )
			{
				Current_Mouse = (HIWORD(lParam)-100)/EH;
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			HBRUSH oldb = (HBRUSH)GetCurrentObject(hdc,OBJ_BRUSH);
			HBRUSH newb ;
			for(int i=0;i<MAP_S;i++)
			{
				switch(map[i])
				{
				case _TL:
					{
						newb = CreateSolidBrush(_TL_C);
						break;
					}
				case _ZA:
					{
						newb = CreateSolidBrush(_ZA_C);
						break;
					}
				case _HERO:
					{
						newb = CreateSolidBrush(_HERO_C);
						break;
					}
				case _XZ:
					{
						newb = CreateSolidBrush(_XZ_C);
						break;
					}
				case _AIM:
					{
						newb = CreateSolidBrush(_AIM_C);
						break;
					}
				case _H_AIM:
					{
						newb = CreateSolidBrush(_H_AIM_C);
						break;
					}
				case _X_AIM:
					{
						newb = CreateSolidBrush(_X_AIM_C);
						break;
					}
				}
				SelectObject(hdc,newb);
				Rectangle(hdc,100+(i%MAP_W)*EW,100+(i/MAP_W)*EH,100+(i%MAP_W)*EW+EW,100+(i/MAP_W)*EH+EH);
				DeleteObject(newb);
			}
			for(int i=0;i<7;i++)
			{
				switch(i)
				{
				case _TL:
					{
						newb = CreateSolidBrush(_TL_C);
						break;
					}
				case _ZA:
					{
						newb = CreateSolidBrush(_ZA_C);
						break;
					}
				case _HERO:
					{
						newb = CreateSolidBrush(_HERO_C);
						break;
					}
				case _XZ:
					{
						newb = CreateSolidBrush(_XZ_C);
						break;
					}
				case _AIM:
					{
						newb = CreateSolidBrush(_AIM_C);
						break;
					}
				case _H_AIM:
					{
						newb = CreateSolidBrush(_H_AIM_C);
						break;
					}
				case _X_AIM:
					{
						newb = CreateSolidBrush(_X_AIM_C);
						break;
					}
				}
				SelectObject(hdc,newb);
				//����ѡ����
				Rectangle(hdc,400,100+i*EH,480,100+i*EH+EH);
				SetBkMode(hdc,TRANSPARENT);

				char buf[256]={0};

				if(Current_Mouse==i)
				{
					strcat_s(buf,256,c[i]);
					strcat_s(buf,256," ��");
					TextOutA(hdc,400,100+i*EH,buf,(int)strlen(buf));
				}else
					TextOutA(hdc,400,100+i*EH,c[i],(int)strlen(c[i]));

				DeleteObject(newb);
			}

			SelectObject(hdc,oldb);
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
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
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

	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							"�����ӹؿ��༭��",//���ڱ���������
							 //WS_THICKFRAME ͨ������϶��ı䴰�ڴ�С
							 //WS_MAXIMIZEBOX �������Ͻǵ���󻯺ͻ�ԭ��ť
							 WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,//���ڷ��
							 r.left,//���ڵ����Ͻ�x����
							 r.top,//���ڵ����Ͻ�y����
							 r.right - r.left,//���ڵĿ����أ�
							 r.bottom - r.top,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0


	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
	UpdateWindow(hWnd);

	

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

