#include <windows.h>
#include<vector>
struct Point
{
	POINT p;
	int time;
};

std::vector<Point> g_vPoint;


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
			if(g_vPoint.size()>1)
			{
				for(std::vector<Point>::iterator i = g_vPoint.begin();i!=g_vPoint.end()-1;i++)
				{
					POINT p;
					MoveToEx(hdc,i->p.x,i->p.y,&p);
					LineTo(hdc,(i+1)->p.x,(i+1)->p.y);
				}
			}
			

			EndPaint(hwnd,&ps);
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			Point p;
			p.p.x=LOWORD(lParam);
			p.p.y=HIWORD(lParam);
			p.time=5;
			g_vPoint.push_back(p);
			InvalidateRect(hwnd,0,TRUE);
			
			return 0;
		}
	case WM_TIMER:
		{
			for(std::vector<Point>::iterator i = g_vPoint.begin();i!=g_vPoint.end();)
			{
				i->time--;
				if(i->time==0)
				{
					i=g_vPoint.erase(i);
				}else
				{
					i++;
				}
			}
			InvalidateRect(hwnd,0,TRUE);
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