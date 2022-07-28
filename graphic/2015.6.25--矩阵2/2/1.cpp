#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <iostream>
#include "Vector2.h"
#include "Matrix3.h"

#pragma comment(lib, "Msimg32.lib")

#define _CLIENT_W 640
#define _CLIENT_H 480
#define _SLEEP_TIME 33

HWND g_hWnd = 0;
BOOL g_Act = TRUE;

void GameInit();
void GameRun();
void GameEnd();

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
#include <vector>
#include "Matrix3.h"

HDC main_dc; //���豸
HDC back_dc; //���豸
HBITMAP back_bmp; //���豸λͼ

bool xz = true; //��ת��־��Ϊ���ʾ��ת��Ϊ�ٱ�ʾ����
float angle = 0.0f; //�Ƕ�
bool add_angle = true; //�Ƕȵ�����־
CVector2 cur; //��ǰ�ĵ�
CVector2 cur1; //��ǰ�ĵ�
float len = 1.0f;
bool sc = true;
CVector2 qiu; //��
float qiu_r; //��İ뾶
bool jz; //��������ı�־

void DrawLine(const CVector2* v1, const CVector2* v2)
{
	MoveToEx(back_dc, v1->x, v1->y, 0);
	LineTo(back_dc, v2->x, v2->y);
}

float get_rand_float(float min, float max)
{
	return (max - min) * (rand() / 32767.0f) + min;
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

	//��ʼ����
	srand(time(0));
	qiu.Set(rand() % _CLIENT_W, rand() % (_CLIENT_H - 100) + 100);
	qiu_r = get_rand_float(10.0f, 50.0f);
}

void GameRun()
{
	//��ת
	if (xz)
	{
		//�Ƕȱ仯
		if (add_angle)
		{
			angle += 0.05f;
			if (angle >= 3.1415926f)
				add_angle = false;
		}
		else
		{
			angle -= 0.05f;
			if (angle <= 0.0f)
				add_angle = true;
		}

		//״̬�ı�
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			len = 100.0f;
			sc = true;
			xz = false;
		}
	}
	else
	{
		if (sc)
		{
			//�õ����������ĵ�λ����
			CVector2 dir = cur - CVector2(_CLIENT_W / 2.0f, 0.0f);
			dir = dir.Normalize();

			//���ȱ仯
			len += 5.0f;

			//�õ���ǰ�Ļ���λ��
			cur1 = len * dir;
			cur1 += CVector2(_CLIENT_W / 2.0f, 0.0f);

			//�ж��Ƿ���������
			if ((cur1 - qiu).Length() < qiu_r)
			{
				sc = false;
				jz = true;
			}

			if (cur1.x < 0 || cur1.x > _CLIENT_W || cur1.y < 0 || cur1.y > _CLIENT_H)
			{
				sc = false;
				jz = false;
				cur1.Set();
			}
		}
		else
		{
			//�õ����������ĵ�λ����
			CVector2 dir = cur - CVector2(_CLIENT_W / 2.0f, 0.0f);
			dir = dir.Normalize();

			//���ȱ仯
			len -= 5.0f;

			//�õ���ǰ�Ļ���λ��
			cur1 = len * dir;
			cur1 += CVector2(_CLIENT_W / 2.0f, 0.0f);

			if (jz)
			{
				qiu = cur1;
			}

			if (len < 100.0f)
			{
				if (jz)
				{
					qiu.Set(rand() % _CLIENT_W, rand() % (_CLIENT_H - 100) + 100);
					qiu_r = get_rand_float(10.0f, 50.0f);
				}
				xz = true;
			}
		}
	}

	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);

	Ellipse(back_dc, qiu.x - qiu_r, qiu.y - qiu_r, qiu.x + qiu_r, qiu.y + qiu_r);
	
	if (xz)
	{
		//������ת����
		CMatrix3 m0;
		m0.Rotate(angle);

		//����ƽ�ƾ���
		CMatrix3 m1;
		m1.Translate(_CLIENT_W / 2.0f, 0.0f);

		//�õ���Ͼ���
		CMatrix3 m2;
		_Mat_X_Mat(&m0, &m1, &m2);

		//�任
		CVector2 v(100.0f, 0.0f);
		_Vec_X_Mat(&v, &m2, &cur);

		CVector2 u(_CLIENT_W / 2.0f, 0.0f);
		DrawLine(&u, &cur);
	}
	else
	{
		CVector2 u(_CLIENT_W / 2.0f, 0.0f);
		DrawLine(&u, &cur1);
	}
	
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);
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