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

CVector2 v[4]; //ԭʼ��������

struct _FK
{
	float angle, add_angle; //�Ƕ���Ƕȵĵ�����
	CVector2 pos; //λ��
	COLORREF color; //��ɫ
};
std::vector<_FK> fangkuai; //����

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

	//���ó�ʼ�ĵ㣨��������ϵ��

	v[0].Set(20,0);
	v[1].Set(0,20);
	v[2].Set(-20,0);
	v[3].Set(0,-20);
}

void DrawLine(const CVector2* v1, const CVector2* v2)
{
	MoveToEx(back_dc, v1->x, v1->y, 0);
	LineTo(back_dc, v2->x, v2->y);
}

float get_rand_float(float min, float max)
{
	return (max - min) * (rand() / 32767.0f) + min;
}

void GameRun()
{
	BitBlt(back_dc, 0, 0, _CLIENT_W, _CLIENT_H, 0, 0, 0, WHITENESS);
	
	//���ݸ��ºͻ���
	for (int i = 0; i < fangkuai.size(); ++i)
	{
		//����
		CMatrix3 m0, m1, m2;
		m0.Rotate(fangkuai[i].angle);
		m1.Translate(fangkuai[i].pos.x, fangkuai[i].pos.y);
		_Mat_X_Mat(&m0, &m1, &m2);

		//�������Ծ���
		CVector2 u[4];
		for (int j = 0; j < 4; ++j)
			_Vec_X_Mat(&v[j], &m2, &u[j]);

		HPEN p1 = CreatePen(PS_SOLID, 1, fangkuai[i].color);
		HPEN p0 = (HPEN)SelectObject(back_dc, p1);

		DrawLine(&u[0], &u[1]);
		DrawLine(&u[1], &u[2]);
		DrawLine(&u[2], &u[3]);
		DrawLine(&u[3], &u[0]);

		//��ת
		fangkuai[i].angle += fangkuai[i].add_angle;

		SelectObject(back_dc, p0);
		DeleteObject(p1);
	}
	
	BitBlt(main_dc, 0, 0, _CLIENT_W, _CLIENT_H, back_dc, 0, 0, SRCCOPY);

	//����ƽ������
	if (GetAsyncKeyState(VK_LBUTTON) & 1)
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(g_hWnd, &p);
		if (p.x >= 0 && p.x < _CLIENT_W && p.y >= 0 && p.y < _CLIENT_H)
		{
			_FK fk;
			fk.pos.Set(p.x, p.y);
			fk.angle = 0.0f;
			fk.add_angle = get_rand_float(0.1f, 1.0f);
			fk.color = RGB(rand() % 256, rand() % 256, rand() % 256);
			fangkuai.push_back(fk);
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