#include <windows.h>
#include<vector>
#include"resource.h"
#include<string>



std::string ss;

std::vector<int> g_vStrlen;

RECT r;
//std::string str;
int color_s = RGB(0,0,0);//��ɫ

HWND g_hwnd[2];

LOGFONT lf;//��������

int flag=0;//�϶��ı��

RECT changeRect;



//GDI (Graphics Device Interface):ͼ���豸�ӿڣ�����windows��
//���ڻ���ͼ�εĸ��ֺ������ṹ�壬����ܳ�.
//����
//������Ϣ��������������������ϵͳ����
INT_PTR __stdcall f(HWND hwndDlg,
					UINT uMsg,
					WPARAM wParam,
					LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
		{
			ShowWindow(g_hwnd[1],SW_HIDE);
			return 1;

		}
	case WM_INITDIALOG:
		{
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == ID1)
				{
					COLORREF custColor[16] =
					{
						//�����������������Զ�����ɫ��ֵ
						RGB(255,0,0),RGB(255,255,255)
					};

					CHOOSECOLOR cc = {};
					cc.lStructSize = sizeof(cc);
					cc.hwndOwner = g_hwnd[1];
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
						color_s =RGB(r,g,b);
						InvalidateRect(g_hwnd[0],&::r,TRUE);
					}
				}else
				if(LOWORD(wParam) == IDCANCEL)
				{
					CHOOSEFONT cf = {};
					cf.lStructSize = sizeof(cf);
					cf.hwndOwner = g_hwnd[1];
					cf.lpLogFont = &lf;
					cf.Flags = CF_SCREENFONTS;

					if(IDOK == ChooseFont(&cf))
					{
						InvalidateRect(g_hwnd[0],&::r,TRUE);
						//lf�ͱ���д������ѡ�����������ԣ�
						//���CreateFontIndirect���ܴ���������
					}
				}
			}else
			if(HIWORD(wParam)==EN_CHANGE)
			{
				g_vStrlen.clear();
				ss.clear();
				HWND hwnd = GetDlgItem(hwndDlg,IDC_EDIT1);
				int r = (int)SendMessage(hwnd,EM_GETLINECOUNT,0,0);
				for(int i=0;i<r;i++)
				{
					char buf[256] = {};
					*((short*)buf) = 256;//ǰ2���ֽ�������Ĵ�С
					SendMessageA(hwnd,EM_GETLINE,i,(__w64 long)buf);
					ss+=buf;
					g_vStrlen.push_back(strlen(buf));
				}
				InvalidateRect(g_hwnd[0],&::r,true);
			}
			return 1;
		}
	}
	return 0;
}


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
			r.left =200;
			r.top = 200;
			r.right =400;
			r.bottom=400;
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
			SetGraphicsMode(hdc,GM_ADVANCED);
			SetBkMode(hdc,TRANSPARENT);
			Rectangle(hdc,r.left,r.top,r.right,r.bottom);
			
			HFONT oldf =(HFONT)GetCurrentObject(hdc,OBJ_FONT);
			HFONT newfont =CreateFontIndirect(&lf);
			(HFONT)SelectObject(hdc,newfont);
			SetTextColor(hdc,(COLORREF)color_s);
			if(flag==0)
			{
				for(int i = 0; i < g_vStrlen.size(); i++)
				{
					int count = 0;
					for(int j = 0; j < i; j++)
					{
						count += g_vStrlen[j];
					}
					char buf[256] = {};

					memcpy_s(buf,255,ss.c_str() + count,g_vStrlen[i]);

					TextOutA(hdc,r.left,r.top + i * 30,buf,strlen(buf));
				}
			}
			

			SelectObject(hdc,oldf);
			DeleteObject(newfont);
			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			r.left=LOWORD(lParam);
			r.top=HIWORD(lParam);
			flag=1;
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			ShowWindow(g_hwnd[1],SW_SHOW);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			if(flag==1)
			{
				r.right=LOWORD(lParam);
				r.bottom=HIWORD(lParam);
				InvalidateRect(hwnd,0,TRUE);
			}
			return 0;
		}
	case WM_LBUTTONUP:
		{
			r.right=LOWORD(lParam);
			r.bottom=HIWORD(lParam);
			flag=0;
			InvalidateRect(hwnd,&r,TRUE);
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

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = 0;

	//���ڵ�����
	wc.lpszClassName = L"�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	
	g_hwnd[0] = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
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

	g_hwnd[1] = CreateDialog(GetModuleHandle(0),//��ȡ�Ի���ľ��
							MAKEINTRESOURCE(IDD_DIALOG1),//�Ի����ID
							g_hwnd[0],//������
							f);//�Ի������Ϣ������

	//04)��ʾ����
	ShowWindow(g_hwnd[0],nCmdShow);
	ShowWindow(g_hwnd[1],SW_SHOW);

	//05)���´���
	UpdateWindow(g_hwnd[0]);

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		//���������WM_KEYDOWN��WM_KEYUP��Ϣ�͸��ݵ�ǰ�����뷨
		//�ڲ���һ��WM_CHAR��Ϣ��Ͷ�ݵ���Ϣ������
		TranslateMessage(&msg);
		//�ɷ���Ϣ�ز���ϵͳ(���ƾ�������DispatchMessage�����ô�����Ϣ����)
		DispatchMessage(&msg);
	}

	return 1;
}