#include <windows.h>
#include "resource.h"
//WM_COMMAND:������Ϣ
//�˵���ؼ�(��ť֮��),��ݼ�����
//wParam
//1�����ֲ���
// a)���������Ϣ�Ǳ��ؼ���������ָ�����ǿؼ��ľ�����Ϣ��
// b)���������Ϣ�Ǳ���ݼ�������Ϊ1
// c)���������Ϣ�Ǳ��˵������Ϊ0
//2)���ֲ���:�򴥷�����������Ϣ�Ĳ˵���ؼ�����ݼ���ID
//lParam
//���������Ϣ�Ǳ��ؼ���������Ϊ�ؼ��Ĵ��ھ��������ǲ˵���
//��ݼ�������Ϊ0

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
				case ID_WM_40001:
					{
						MessageBox(hwnd,"����",0,0);
						break;
					}
				case ID_WM_40005:
					{
						DestroyWindow(hwnd);
						break;
					}
				case ID_WM_40006:
					{
						MessageBox(hwnd,"����",0,0);
						break;
					}
				case ID_22222_2RTRTT:
					{
						MessageBox(hwnd,"RTRTT",0,0);
						break;
					}
				}
			}
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
	//HICON LoadIcon(����ͼ��
	//HINSTANCE hInstance,//��Ҫʹ�õ�ͼ���Ǵ����exe�ļ��е���Դ
	//                      ��˴�������дӦ�ó����ʵ��������������
	//                      ��0����.  
	//LPCSTR lpIconName);//ͼ����ַ���ID�����ͼ���Ǵ����exe�ļ��е���Դ
	//                     �����õ���ͼ��ID��������������
	//                     MAKEINTRESOURCE�꽫��ת��Ϊ�ַ�����ʽ
	wc.hIcon = LoadIcon(0,IDI_APPLICATION);

	//���
	//HCURSOR LoadCursor(���ع��
	//HINSTANCE hInstance,//��Ҫʹ�õĹ���Ǵ����exe�ļ��е���Դ
	//                      ��˴�������дӦ�ó����ʵ��������������
	//                      ��0����.  
    //LPCSTR lpCursorName);�����ַ���ID�����ͼ���Ǵ����exe�ļ��е���Դ
	//                     �����õ��Ĺ��ID��������������
	//                     MAKEINTRESOURCE�꽫��ת��Ϊ�ַ�����ʽ
	wc.hCursor = LoadCursor(0,IDC_ARROW);

	//HBRUSH ��ˢ
	//����ϵͳ���ڻ��ƴ��ڱ����ı�����ˢ
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵��ַ���ID�����û������0
	wc.lpszMenuName = 0;

	//���ڵ�����
	wc.lpszClassName = "�˰�";

	//02)ע�����õĴ���
	RegisterClass(&wc);
	//һ���������Ľṹ��������ڴ������������
	//,�ṹ������д��ĳЩ��Ա������������ͼ�꣬��꣩
	//�;������½ṹ�崴�����������еĴ��ڵĹ���,��
	//ÿ������Ҳ���Լ���һ���Ķ���������˵��С,λ�ã��Ƿ���
	//�˵��ȵ�
	
	//������Դ�еĲ˵���һ���˵������
	//����2
	HMENU hmenu = LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1));

	//03)�ô������ṹ������������
	HWND hWnd = CreateWindow(wc.lpszClassName,//�������ṹ������ƣ�����ϵͳ�����
		                    //������������ҵ�ע��Ĵ��ڣ�Ȼ��ʹ������������Ľṹ��
							 //������ɴ������ڵ�����
							 "WM_COMMAND",//���ڱ���������
							 WS_OVERLAPPEDWINDOW,//���ڷ��
							 CW_USEDEFAULT,//���ڵ����Ͻ�x����
							 CW_USEDEFAULT,//���ڵ����Ͻ�y����
							 CW_USEDEFAULT,//���ڵĿ����أ�
							 CW_USEDEFAULT,//���ڵĸߣ����أ�
							 HWND_DESKTOP,//�����ڴ��ھ��,HWND_DESKTOP��ʾ����
							 hmenu,//���ڲ˵��������ʹ�ò˵���0
							 wc.hInstance,//Ӧ�ó���ʵ�����
							 0);//�����ַ���õ�ַ����ͨ��WM_CREATE��Ϣ�õ�����ʹ������Ϊ0

	//04)��ʾ����
	ShowWindow(hWnd,nCmdShow);

	//05)���´���
	UpdateWindow(hWnd);

	//06)��Ϣѭ��
	//��Ϣ�ṹ��
	//struct MSG
	//{
	//	HWND hwnd;//��������Ĵ���
	//	UINT message;//��Ϣ����
	//	WPARAM wParam;//��Ϣ���Ӳ���1,��ͬ����Ϣ���岻ͬ
	//	LPARAM lParam;//��Ϣ���Ӳ���2,��ͬ����Ϣ���岻ͬ
	//	DWORD time;//���������ʱ��
	//	POINT pt;//��������ʱ������ڵ�λ��(������������)
	//};
	//1)windows��Ϊÿ���߳�ά��һ����Ϣ����<MSG>
	//2)windows����ʱ��صļ��ÿ���������Ƿ���ĳЩ�ض����¼�
	//  ��ôwindows�ͻ�������������һ��MSG�ṹ�壬�����ýṹ��
	//  ���뵽����������ڵ��̵߳���Ϣ�����У���������ĳ����������
	//  ����������,��windows�����һ��MSG����.
	//  MSG msg;
	//  msg.hwnd = hWnd;
	//  msg.message = WM_LBUTTONDOWN;
	//  msg.wParam = MK_LBUTTON;
	//  msg.lParam = MAKELONG(���x���꣬���y����);(����ڴ��ڿͻ���)
	//	MAKELONG(WORD1,WORD2)��WORD1��WORD2��ϳ�һ��DWORD
    //  msg.time = �����¼���ʱ��
	//  msg.pt = �����¼�ʱ������ڵ�λ��(���������)
	//  �����(��Ϣ���У�msg)��
	//3)����Ӧ����GetMessage������PeekMessage���Ӷ�����
	//  ȡ����Ϣ����������صĴ���,Ȼ����Ϣ����������ϵͳ
	//4)����ϵͳ����������ڴ������ṹ�������õĴ�����Ϣ����
	//  ���������Ƿ���������ϵͳ����Ϣ.
	//  ����Ϣ������ȡ��ͷ��Ϣ�������ǰû����Ϣ�͵ȴ�
	//GetMessage(
 //   LPMSG lpMsg,//���ڻ�ȡ��Ϣ����Ϣ�ṹ���ַ
 //   HWND hWnd,//ָ����ȡ��Ϣ�Ĵ��ڣ�Ϊ0���ȡ��ǰ�߳������д��ڵ���Ϣ
 //   UINT wMsgFilterMin,//��Ϣ���˵�����
 //   UINT wMsgFilterMax);//��Ϣ���˵�����

	//����õ�����ϢWM_QUIT��Ϣ�ͷ��ؼ�.
	//��֮�ͷ����档
	//��������ӵ��þ�ֻ�ܻ�ȡ��hWnd������Ĵ��ڵ���Ϣ�����Ҳ���õ���
	//WM_LBUTTONDOWN��WM_RBUTTONDBLCLK֮�����Ϣ
	//GetMessage(&msg,hWnd,WM_LBUTTONDOWN,WM_RBUTTONDBLCLK);

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