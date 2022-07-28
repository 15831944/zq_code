#include <windows.h>
#include<vector>
#include"resource.h"

#define JX true
#define YX false

struct Rect
{
	RECT r;
	int pc;//���ʵ���ɫ
	int bc;//��ˢ����ɫ
	bool isJx;
};
Rect r;
std::vector<Rect> g_vRect;
bool flag = JX;
int PC  =  RGB(0,0,0);
int BC  =  RGB(255,255,255);


//GDI (Graphics Device Interface):ͼ���豸�ӿڣ�����windows��
//���ڻ���ͼ�εĸ��ֺ������ṹ�壬����ܳ�.
//����
//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	//������Ϣ������ʽ
	//1)���ϵͳ�˵��Ĺرղ˵��Alt + F4��
	//2)���Ͻǵ�X��ť
	case WM_CREATE:
		{
			char buf[256]={};
			sprintf_s(buf,256,"���Ρ�����(0,0,0),��ˢ(255,255,255)");
			SetWindowTextA(hwnd,buf);
			return 0;
		}
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			
			for(std::vector<Rect>::iterator i = g_vRect.begin();i!=g_vRect.end();i++)
			{
				HBRUSH oldb =(HBRUSH)GetCurrentObject(hdc,OBJ_BRUSH);
				HPEN oldp = (HPEN)GetCurrentObject(hdc,OBJ_PEN);
				HPEN newpen = CreatePen(
				PS_SOLID,//���
				1,//��ȣ������ȴ���1����ô���ֻ����PS_SOLID
				i->pc);//��ɫ
				HBRUSH newbrush = CreateSolidBrush(i->bc);
				SelectObject(hdc,newpen);
				SelectObject(hdc,newbrush);
				if(i->isJx)
				{
					Rectangle(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				}else
				{
					Ellipse(hdc,i->r.left,i->r.top,i->r.right,i->r.bottom);
				}
				SelectObject(hdc,oldp);
				SelectObject(hdc,oldb);
				DeleteObject(newbrush);
				DeleteObject(newpen);
			}
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			r.r.left=LOWORD(lParam);
			r.r.top=HIWORD(lParam);
			return 0;
		}
	case WM_LBUTTONUP:
		{
			r.r.right=LOWORD(lParam);
			r.r.bottom=HIWORD(lParam);
			r.isJx=flag;
			r.pc =PC;
			r.bc =BC;
			g_vRect.push_back(r);
			InvalidateRect(hwnd,0,TRUE);
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
						flag = JX;
						break;
					}
				case ID_40002:
					{
						flag =YX;
						break;
					}
				case ID_40003:
					{
						COLORREF custColor[16] =
						{
							//�����������������Զ�����ɫ��ֵ
							RGB(255,0,0),RGB(255,255,255)
						};

						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;

						//��ɫ����R G B ��ԭɫ��϶��ɵ�
						// ����ԭɫ��ȡֵ��Χ�� 0-255
						//����һ����unsigned char����¼���ǵ�ÿ����ɫ����
						//����ɫ�Ի���
						if(IDOK == ChooseColor(&cc))
						{
							COLORREF color = cc.rgbResult;

							unsigned char r =  GetRValue(color);
							unsigned char g =  GetGValue(color);
							unsigned char b =  GetBValue(color);
							PC =RGB(r,g,b);
							char buf[256]={};
							sprintf_s(buf,256,"���Ρ�����(%d,%d,%d),��ˢ(%d,%d,%d)",
									GetRValue(PC),GetGValue(PC),GetBValue(PC),
									GetRValue(BC),GetGValue(BC),GetBValue(BC));
							SetWindowTextA(hwnd,buf);
						}
						break;
					}
				case ID_40004:
					{
						COLORREF custColor[16] =
						{
							//�����������������Զ�����ɫ��ֵ
							RGB(255,0,0),RGB(255,255,255)
						};

						CHOOSECOLOR cc = {};
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hwnd;
						cc.lpCustColors = custColor;

						//��ɫ����R G B ��ԭɫ��϶��ɵ�
						// ����ԭɫ��ȡֵ��Χ�� 0-255
						//����һ����unsigned char����¼���ǵ�ÿ����ɫ����
						//����ɫ�Ի���
						if(IDOK == ChooseColor(&cc))
						{
							COLORREF color = cc.rgbResult;

							unsigned char r =  GetRValue(color);
							unsigned char g =  GetGValue(color);
							unsigned char b =  GetBValue(color);
							BC =RGB(r,g,b);
							char buf[256]={};
							sprintf_s(buf,256,"���Ρ�����(%d,%d,%d),��ˢ(%d,%d,%d)",
									GetRValue(PC),GetGValue(PC),GetBValue(PC),
									GetRValue(BC),GetGValue(BC),GetBValue(BC));
							SetWindowTextA(hwnd,buf);
						}
						break;
					}	
				}
				return 0;
			}
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

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	//���ڵ�����
	wc.lpszClassName = L"�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 L"����",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 0,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//04)��ʾ����
	SetTimer(hWnd,1,200,0);
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}
	KillTimer(hWnd,1);

	return 1;
}