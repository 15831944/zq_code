#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

HWND g_hWnd = 0;
BOOL g_Act = TRUE;

void GameInit();
void GameRun();
void GameEnd();

extern int speed;
void SetSpeed();

LRESULT CALLBACK WindowProc(HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_ACTIVATEAPP:
		{
			g_Act = (BOOL)wParam;
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
			if (WHEEL_DELTA == (short)HIWORD(wParam) && speed < 32)
				speed += 1;
			else if (-WHEEL_DELTA == (short)HIWORD(wParam) && speed > 1)
			{
				speed -= 1;
			}
			SetSpeed();
			return 0;
		}
	}
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //���ڷ��
		FALSE); //���޲˵�

	g_hWnd = CreateWindowA(
		wc.lpszClassName, //ʹ�õĴ������ṹ�������
		"hello world", //���ڱ���������
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		cr.left, //�������Ͻ�x����
		cr.top, //�������Ͻ�y����
		cr.right - cr.left, //���ڿ�
		cr.bottom - cr.top, //���ڸ�
		HWND_DESKTOP, //�����ڣ�һ����˵��д���洰��
		0, //�˵���������þ���д0
		wc.hInstance, //Ӧ�ó���ʵ�����
		0); //��������

	//��Ϸ��ʼ��
	GameInit();

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//�鿴��ǰ�Ķ�ͷ��Ϣ���������Ϣ�ͷ����棬û����Ϣ�ͷ��ؼ�
	//BOOL PeekMessage(
	//	LPMSG lpMsg, //�õ���ͷ��Ϣ����Ϣ�ṹ��
	//	HWND hWnd, //���ڣ�Ϊ0��õ���ǰ�߳��д��������д��ڵ���Ϣ
	//	UINT wMsgFilterMin, //��Ϣ��������
	//	UINT wMsgFilterMax, //��Ϣ��������
	//	UINT wRemoveMsg); //PM_REMOVE��ʾ�鿴����Ϣ֮�������Ϣ������ɾ����PM_NOREMOVE��ʾ�����鿴��Ϣ�����Ὣ�鿴������Ϣ�Ӷ�����ɾ��

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		//�������Ϣ������Ϸѭ���ʹ�����Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//���û����Ϣ�䵱ǰ����Ϊ����״̬��ִ����Ϸѭ��
		else if (g_Act)
		{
			//ÿ֡��ʼ��ʱ��
			int t0 = GetTickCount();

			//��Ϸ����
			GameRun();

			//ÿ֡��Ϸʱ��Ĵ���
			int t1 = GetTickCount() - t0;
			Sleep(t1 < _SLEEP_TIME ? _SLEEP_TIME - t1 : 1);
		}
		else
		//���û����Ϣ�䵱ǰ����δ������͵ȴ���Ϣ
			WaitMessage();
	}

	//��Ϸ����
	GameEnd();

	return 1;
}

#include <time.h>

HDC main_dc; //���豸
HDC back_dc; //���豸
HBITMAP back_bmp; //���豸λͼ

#define _R 20
#define _SPEED 10
#define _MCL 0.05f

struct _SPHERE //��
{
	CVector2 pos; //λ��
	CVector2 speed; //�ٶ�
};
_SPHERE Sphere[10]; //��0��Ϊ����
int speed; //�����ٶ�

void SetSpeed()
{
	char buf[64];
	sprintf_s(buf, 64, "�����ٶ�:%d", speed);
	SetWindowTextA(g_hWnd, buf);
}

void GameInit()
{
	//�õ�����ͼ�豸
	main_dc = GetDC(g_hWnd);

	//�õ����豸
	back_dc  = CreateCompatibleDC(main_dc);

	//�������豸λͼ
	back_bmp = CreateCompatibleBitmap(main_dc, _CLIENT_W, _CLIENT_H);

	//�����豸λͼѡ����豸
	DeleteObject(SelectObject(back_dc, back_bmp));

	//��ʼ������λ��
	Sphere[0].pos.Set(_CLIENT_W * 0.25f, _CLIENT_H / 2);

	//��ʼ��������
	for (int i = 1; i < 10; ++i)
	{
		Sphere[i].pos.Set(_CLIENT_W * 0.75f, i * 45);
	}

	//��ʼ�������ٶ�
	speed = 16;
	SetSpeed();
}

void GameRun()
{
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);
	
	for (int i = 0; i < 10; ++i)
	{
		Ellipse(back_dc, Sphere[i].pos.x - _R, Sphere[i].pos.y - _R, Sphere[i].pos.x + _R, Sphere[i].pos.y + _R);
		char buf[32];
		sprintf_s(buf, 32, "%d", i);
		TextOutA(back_dc, Sphere[i].pos.x, Sphere[i].pos.y, buf, strlen(buf));
	}

	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);

	//���������ǽ�ڵ���ײ
	for (int i = 0; i < 10; ++i)
	{
		//�߼�
		if (!_IS_ZERO(Sphere[i].speed.Length()))
		{
			Sphere[i].pos += Sphere[i].speed;

			//��ǽ�����ײ

			//x����
			if (Sphere[i].pos.x - _R <= 0.0f || Sphere[i].pos.x + _R >= _CLIENT_W)
			{
				if (Sphere[i].pos.x - _R <= 0.0f)
					Sphere[i].pos.x = _R;
				else
					Sphere[i].pos.x = _CLIENT_W - _R;

				Sphere[i].speed.x = -Sphere[i].speed.x;
			}
			//y����
			if (Sphere[i].pos.y - _R <= 0.0f || Sphere[i].pos.y + _R >= _CLIENT_H)
			{
				if (Sphere[i].pos.y - _R <= 0.0f)
					Sphere[i].pos.y = _R;
				else
					Sphere[i].pos.y = _CLIENT_H - _R;

				Sphere[i].speed.y = -Sphere[i].speed.y;
			}

			float len = Sphere[i].speed.Length();
			CVector2 nor = Sphere[i].speed.Normalize();
			len -= _MCL;
			if (len <= 0.0f)
				Sphere[i].speed.Set();
			else
				Sphere[i].speed = nor * len;
		}
	}

	//����������������ײ
	for (int i = 0; i < 9; ++i)
	{
		for (int j = i + 1; j < 10; ++j)
		{
			//v��������i����j��������������
			CVector2 v = Sphere[i].pos - Sphere[j].pos;
			if (v.Length() < 2 * _R)
			{
				//��������ֿ�
				CVector2 u = v.Normalize();
				CVector2 w = u * (2 * _R - v.Length());
				Sphere[i].pos += w;

				//������ײ֮����ٶ�

				//�õ����������������������ͶӰ
				CVector2 vi1 = Sphere[i].speed.Shadow(-v);
				CVector2 vi2 = Sphere[i].speed - vi1;
				CVector2 vj1 = Sphere[j].speed.Shadow(v);
				CVector2 vj2 = Sphere[j].speed - vj1;

				//�����ٶ�
				Sphere[i].speed = vi2 + vj1;
				Sphere[j].speed = vj2 + vi1;
			}
		}
	}

	//����
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		//�õ������������������
		POINT p;
		GetCursorPos(&p);

		//���������ת��Ϊ���ڿͻ���������
		ScreenToClient(g_hWnd, &p);

		//�ڿͻ�����
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			Sphere[0].speed = CVector2(p.x, p.y) - Sphere[0].pos;
			Sphere[0].speed = Sphere[0].speed.Normalize() * speed;
		}
	}
}

void GameEnd()
{
	//�ͷź��豸λͼ
	DeleteObject(back_bmp);

	//�ͷź��豸
	DeleteDC(back_dc);

	//�ͷ�����ͼ�豸
	ReleaseDC(g_hWnd, main_dc);
}