#include <windows.h>

#define _CLIENT_W 640
#define _CLIENT_H 480

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg, //��Ϣֵ
							WPARAM wParam, //��Ϣ�ĸ��Ӳ���1
							LPARAM lParam) //��Ϣ�ĸ��Ӳ���2
{
	//�������Ǵ��������Ϣ����Ӧ�÷���0

	switch (uMsg)
	{
	case WM_CREATE: //����
		{
			//WM_CREATE�Ǵ��ڸոձ���
			//��������ʱ�򱻴�����
			OutputDebugStringA("WM_CREATE\n"); //��ʾ�ַ������������
			return 0;
		}
	case WM_ACTIVATEAPP: //����򷴼���
		{
			//����������״̬��һ���Ǽ������һ����
			//�Ǽ����ν����״̬���Ǵ���λ��������
			//������ϲ㣬����Ϣ�Ǵ��ڴӷǼ����Ϊ��
			//����ߴӼ����Ϊ�Ǽ����ʱ�򴥷��ģ�
			//ע��wParam���ΪTRUE��ʾ�ӷǼ����Ϊ��
			//����ΪFALSE��ʾ�Ӽ����Ϊ�Ǽ���
			if (wParam == TRUE)
				OutputDebugStringA("WM_ACTIVATEAPP - �Ǽ���->����\n");
			else
				OutputDebugStringA("WM_ACTIVATEAPP - ����->�Ǽ���\n");
			return 0;
		}
	case WM_CLOSE: //�ر�
		{
			//����������Ͻ�[X]���ߵ��ϵͳ�˵���[��
			//��]����Alt+F4���ͻᴥ������Ϣ��Ĭ����Ϣ
			//������DefWindowProc�Ա���Ϣ�Ĵ����ǵ�
			//��DestroyWindow�����ٴ��ڣ�����DestroyWindow
			//������Ͷ��һ��WM_DESTROY��Ϣ����Ϣ������
			//����������������ܱ���Ϣ��ô������Ȼ��
			//�յ�WM_DESTROY��Ϣ��ע�������յ�WM_DESTROY
			//��Ϣ��ʱ�򴰿��Ѿ�������

			int r = MessageBoxA(hwnd, "�Ƿ�رգ�", "��ʾ", MB_YESNO);

			//����ͨ����Ϣ��ķ���ֵ��ȷ�������ʲô��ť�˳���
			if (r == IDYES)
				break; //����switch������DefWindowProc��������Ϣ
			else
				return 0;
		}
	case WM_DESTROY: //����
		{
			//���ڱ�����֮���յ�����Ϣ����ʱ�����Ѿ�����ʹ���ˣ�һ
			//����˵�����ǻ��ڱ���Ϣ�е���PostQuitMessage���������
			//�����þ�������Ϣ������Ͷ��һ��WM_QUIT��Ϣ�������Ϣ��
			//����GetMessage�������ؼ�
			PostQuitMessage(0);
			return 0;
		}
	case WM_QUIT: //�˳�
		{
			//WM_QUIT��Ϣ�ᵼ����Ϣѭ�����˳��������ڱ�����
			//�и����ղ���WM_QUIT��Ϣ
			return 0;
		}
	}

	//������һ������WM_CLOSE�ͻ����DestroyWindow��
	//���ٴ��ڣ�����DestroyWindow��Ͷ��һ��WM_DESTROY
	//��Ϣ�����̵߳���Ϣ�����У����Խ��������Ǿͻ�
	//�������switch�����յ�WM_DESTROY��Ϣ
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "123abc";

	RegisterClass(&wc);

	//���Ը��ݿͻ�����С�����㴰�ڴ�С
	int sw = GetSystemMetrics(SM_CXSCREEN); //�õ�����Ŀ�
	int sh = GetSystemMetrics(SM_CYSCREEN); //�õ�����ĸ�
	RECT cr //cr�õ��ͻ�����λ�á��ߴ�
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		(sw - _CLIENT_W) / 2 + _CLIENT_W,
		(sh - _CLIENT_H) / 2 + _CLIENT_H
	};
	//���ݴ���Ŀͻ���λ�á��ߴ������㴰��Ӧ���е�λ�á��ߴ�
	AdjustWindowRect(
		&cr, //�ͻ������Σ�������ִ�����֮������봰�ھ���
		WS_OVERLAPPEDWINDOW, //���ڷ��
		FALSE); //���޲˵�

	HWND hwnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPEDWINDOW, //���ڷ��
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//���Եõ��ͻ����ĳߴ�
	RECT r; //���νṹ�壺���Ͻǣ�left��top�������½ǣ�right��bottom��
	GetClientRect(hwnd, &r);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}