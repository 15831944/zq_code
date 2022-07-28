#include <windows.h>

//ͨ�öԻ���
//�ļ���
//�ļ�����
//��ɫ�Ի���
//����Ի���

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
	case WM_KEYDOWN:
		{
			if(wParam == VK_F1)
			{
				//�����[]�е�ֵ�������ܴ���ٸ��Զ�����ɫ������
				//���ڶԻ������Զ�����ɫ�Ŀ�ֻ��16����������������16
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
				}
			}
			else if(wParam == VK_F2)
			{
				LOGFONT lf;
				CHOOSEFONT cf = {};
				cf.lStructSize = sizeof(cf);
				cf.hwndOwner = hwnd;
				cf.lpLogFont = &lf;
				cf.Flags = CF_SCREENFONTS;

				if(IDOK == ChooseFont(&cf))
				{
					int a = 0;
					//lf�ͱ���д������ѡ�����������ԣ�
					//���CreateFontIndirect���ܴ���������
				}
			}
			return 0;
		}
	case WM_RBUTTONDOWN:
		{
			char buf[MAX_PATH]	= {};
			OPENFILENAME ofn = {};
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = buf;
			ofn.nMaxFile = MAX_PATH;

			//�򿪱����ļ��Ի���
			//���ѡ��ȷ�������OPENFILENAME�����ĳЩ�����������
			//if(IDOK == GetSaveFileName(&ofn))
			//{
			//	SetWindowText(hwnd,buf);
			//}
			//���ļ��򿪶Ի���
			if(IDOK == GetOpenFileName(&ofn))
			{
				SetWindowText(hwnd,buf);
			}


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
	wc.lpszClassName = "�˰�";
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "ͨ�öԻ���-�ļ�������򿪶Ի���",//���ڱ���������
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
	
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}