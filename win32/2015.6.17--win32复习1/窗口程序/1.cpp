#include <windows.h>

//WinMain�Ǵ��ڳ������ڵ㺯��
//hInstance�����������Լ���Ӧ�ó���ʵ�������һ��exe�ļ��������ɶ��ʵ������������������ĳ���
//hPrevInstance��������һ����������Ӧ�ó���ʵ���ľ����Win32����и��ββ���ʹ���ˣ����ᱻ����Ϊ0��
//lpCmdLine���������ʵ�����ַ���
//nCmdShow������ϵͳ���ݵ�ǰ������������ǵĴ��ڵ���ʾ��ʽ����������ShowWindow����

//��Windows������о���ĸ����ν�����������Ҫע��
//1������ı��ʶ���ָ��
//2����������Ǵ�����ĳ�ֳ�������еĳ�������
//3��Windows������д����ľ������Щ������Ͷ���H��ͷ
//������C����У�C����˳����������ʵ���õ��˾�����ָ���
//typedef struct _SQLIST
//{
//	int size;
//	int length;
//	DATA* data;
//}* SQLIST;
//SQLIST createSQLIST();
//void destroySQLIST(SQLIST sqlist);
//bool insertSQLIST(SQLIST sqlist, DATA data, int pos);
//...
//SQLIST������ͱ������һ��ָ�룬�����ǵĳ�������������˳��
//��ĳ��������������һ�����
//HINSTANCE�ı�����HINSTANCE__�ṹ�����͵�ָ�룬������һ��Ӧ�ó���ʵ��
//struct HINSTANCE__
//{
//	int unused;
//};
//typedef struct HINSTANCE__* HINSTANCE;

//��Windows����У����ǳ�Ա�������ַ����Ľṹ�塢��ʽ�����򷵻�ֵ��
//�ַ����ĺ�������ʵ���������汾��һ����A�汾��һ����W�汾��A�汾��
//���ֽ��ַ�����char*����W�汾��˫�ֽ��ַ�����wchar_t*���������ڴ���
//�б���д��MessageBox����ʵ�������һ����������һ���꣬���������
//��ǰ�������Ƿ�����UNICODE�������������Ǳ�MessageBoxA����MessageBoxW
//���滻��UNICODE�궨����������[��Ŀ]->[����]->[����]->[�ַ���]��
//���е��������ѡ����Unicode�ַ�������ô�������ڱ�����Ŀ��ʱ����Զ�
//������cpp������֮ǰ����UNICODE�꣬�⽫���º����ĺ��W�汾�滻����֮
//�������ѡ����ֽ��ַ�������ô��û��UNICODE�꣬���еĺ����ĺ�ᱻA
//�汾���滻��Ҳ�����ڳ�������ʾָ��������A����W�汾

//�����ĵ��÷�ʽ����Ҫ�Ǻͺ�������ʽ������ջ��˳���й�ϵ���Լ���
//˭���ͷ�ջ�ڴ��й�ϵ��һ��ı�����������������Щ����
//__cdecl����ʽ������ջ˳���Ǵ��ҵ��󣬵��������ջ�ڴ棨�������Ҳ�г�ջ��
//__stdcall����ʽ������ջ˳���Ǵ��ҵ��󣬱����������ջ�ڴ�
//__fastcall��ǰ����С�ڵ���4�ֽڵĲ���������ECX��EDX�Ĵ�����������ʽ������ջ˳���Ǵ��ҵ��󣬱����������ջ�ڴ�
//�����Լ�д�ĺ����ǿ�����[��Ŀ][����][C\C++][�߼�][����Լ��]��ѡ���

//__w64 long __stdcall WindowProc(HWND__* hwnd,
//								unsigned int uMsg,
//								__w64 unsigned int wParam,
//								__w64 long lParam)
//{
//	__w64 long ����64λ��long
//	__w64 unsigned int ����64λ��unsigned int
//}

//������Ϣ�������Ǳ�����ϵͳ���õģ������Ϣ��
//��ֵ����Ϣ�ĸ��Ӳ������ݸ��������
LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //��Ϣֵ
							WPARAM wParam, //��Ϣ�ĸ��Ӳ���1
							LPARAM lParam) //��Ϣ�ĸ��Ӳ���2
{
	switch (uMsg)
	{
		//�����ǵ�����Ͻ�X��ʱ��Windows��⵽�������֮��
		//�ͻ����һ��WM_DESTROY��ϢͶ�ݵ���Ϣ�����У�Ȼ��
		//���ǵ�GetMessageȡ�ã�����ֻ�������ϵͳ����������
		//�����������������Ϣ
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ����Ϣ�����У��⽫��
			//��GetMessage���ؼ٣��˳�����
			PostQuitMessage(0);
			return 0;
		}
	}

	//���ǳ����в����ĵ���Ϣ����DefWindowProc������
	//����DefWindowProc���������þ���ϵͳĬ�ϵĶ�
	//������Ϣ�Ĵ���
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//void f1()
//{
//	int a = 1;
//}
//void f2()
//{
//	int a = 2;
//}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	//f1();
	//f2();
	//����ĵ��û�ʹ��f1��f2�е�a����һ����ַ����

	//��Ϣ��
	//MessageBox(
	//	HWND_DESKTOP, //���ھ����HWND_DESKTOP����������
	//	"abc", //����
	//	"123", //����
	//	MB_OK); //����
	//MessageBoxA(0, "abc", "123", 0);
	//MessageBoxW(0, L"abc", L"123", 0);

	//1����䴰�����ṹ��
	WNDCLASS wc;

	//���������
	//CS_HREDRAW����ʾ�����ڵ�ˮƽ�ߴ緢���ı��ʱ����ô�ػ洰��
	//CS_VREDRAW����ʾ�����ڵĴ�ֱ�ߴ緢���ı��ʱ����ô�ػ洰��
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//������Ϣ������
	wc.lpfnWndProc = WindowProc;

	//����Ǵ�����𡢴���ʹ���˶�����ֽڣ���ô����ζ�Ų���ϵͳ
	//��ע�ᴰ����𡢴������ڵ�ʱ������������ָ���ֽ����Ķ���
	//�棬���ǿ���ͨ��һЩ�������õ���Щ�ڴ�ĵ�ַ����ʹ�ã�����
	//����ͨ��WM_CREATE��Ϣ�õ����ڵĶ����ֽڣ��������ϣ������
	//�����ֽ���ô��д0����

	//������������ֽ�
	wc.cbClsExtra = 0;

	//���ڶ�����ֽ�
	wc.cbWndExtra = 0;

	//Ӧ�ó���ʵ�����
	wc.hInstance = hInstance;

	//ͼ��
	//HICON LoadIcon( //����1��ͼ�겢���ش����ͼ��ľ��
	//	HINSTANCE hInstance, //����Ǵ���Դ�м�����ô��дӦ�ó���ʵ�����������Ǵ��ⲿ�ļ���Windows����ͼ���м�����д0
	//	LPCTSTR lpIconName); //ͼ�������
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);

	//���
	//HCURSOR LoadCursor( //����1����겢���ش���ù��ľ��
	//	HINSTANCE hInstance, //����Ǵ���Դ�м�����ô��дӦ�ó���ʵ�����������Ǵ��ⲿ�ļ���Windows���й���м�����д0
	//	LPCTSTR lpCursorName); //��������
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	//������ˢ
	//����ϵͳ���������ˢ��������Ǵ��ڵĿͻ���
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//�˵�
	//��д0��ʾ��ʹ�ò˵�
	wc.lpszMenuName = 0;

	//�������ṹ�������
	wc.lpszClassName = "123abc";

	//2��ע�ᴰ�����ṹ��
	RegisterClass(&wc);

	//����������ṹ����ʹ���˲˵������������ڵ�ʱ��Ҳָ��
	//�˲˵�����ô��ʹ�ô�������ʱ��ָ���Ĳ˵��������������
	//��ʱ��û��ָ���˵�����ô���ô������ṹ����ָ���Ĳ˵�
	//�������б�ָ���Ĵ������ṹ�����ɵĴ��ڶ���ӵ�д�����
	//��ṹ����ָ���Ĳ˵�ֻҪ�������ڵ�ʱ��˵���0

	//3�����ɴ���
	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPEDWINDOW, //���ڷ��
		100, //�������Ͻ�x����
		100, //�������Ͻ�y����
		640, //���ڿ�
		480, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//4����ʾ����
	ShowWindow(hwnd, nCmdShow);

	//5�����´��ڣ����ʾ�������Ϣ������Ͷ��һ��WM_PAINT��Ϣ
	UpdateWindow(hwnd);

	//6����Ϣѭ��

	//1��WindowsΪÿ���߳�ά��һ����Ϣ����queue<MSG>
	//2��Windows��ʱ��ض��ڼ��ӵ�ǰ����ϵͳ�е�ÿ���߳�
	//   ����������ÿ�����ڣ�һ����������������淢����ĳ
	//   �ּȶ������飨����������������������������水
	//   �£���Щ�ȶ������鶼��Windows�Ѿ��趨�õ��ˣ�����
	//   �ú�WM_XXX��ʾ����Windows����дһ��MSG�ṹ�����
	//   Ȼ������ṹ������뵽�������������ڵ��̵߳���Ϣ
	//   �����У���MSG�ṹ������о��жԵ�ǰ�������������
	//   ����������������WM_LBUTTONDOWN������lParam�����о�
	//   �ǰ���������ʱ���������
	//	struct MSG
	//	{
	//		HWND        hwnd;
	//		UINT        message; //�˴��ᱻ����ΪWM_LBUTTONDOWN
	//		WPARAM      wParam;
	//		LPARAM      lParam; //����д���굱ǰ������
	//		DWORD       time;
	//		POINT       pt;
	//	};
	//3��Ӧ�ó���һ��Ӧ����GetMessage����PeekMessage����Ϣ
	//   �����еõ���ͷ��Ϣ��Ȼ����б�Ҫ�Ĵ�������һ����
	//   ����Ҫ�����������֣���ô��Ӧ����TranslateMessage��
	//   ������Ϣ����Ϊ�ַ���Ϣ�����������֮���ٵ���DispatchMessage
	//   ����Ϣ�ɷ��ز���ϵͳ
	//4������ϵͳ������������ڴ������ṹ������д�Ĵ���
	//   ��Ϣ�����������������Ϣ

	//����Ϣ�����еõ���ͷ��Ϣ�����û�о�
	//�ȴ�������о͵õ������أ�����õ���
	//��Ϣ��WM_QUIT��Ϣ���򱾺������ؼ٣���
	//ֻ֮Ҫ����WM_QUIT��Ϣ�ͷ�����
	//BOOL GetMessage(
	//	LPMSG lpMsg, //����Ϣ������ȡ������Ϣ
	//	HWND hWnd, //Ҫ�õ���Ϣ��Ŀ�괰�ڣ����Ϊ0����õ����̴߳��������д��ڵ���Ϣ
	//	UINT wMsgFilterMin, //��Ϣ��������
	//	UINT wMsgFilterMax); //��Ϣ��������

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

//HINSTANCE��Ӧ�ó���ʵ�����
//HICON��ͼ����
//HCURSOR�������
//HBRUSH����ˢ���
//HWND�����ھ��