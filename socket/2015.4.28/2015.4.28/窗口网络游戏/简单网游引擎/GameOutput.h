#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include <windows.h>
#include <string>
#include "Map.h"

#define _MIRROR_NONE 0 //������
#define _MIRROR_LR 1 //���Ҿ���
#define _MIRROR_TB 2 //���¾���
#define _MIRROR_TBLR 3 //�������Ҿ���

class CGameOutput
{
	HWND m_hWnd;
	int m_ClientW;
	int m_ClientH;
	HDC m_MainDC;
	HDC m_BackDC;
	HDC m_MirrorDC;
	CMap<std::string, HDC> m_Bitmaps;
	CMap<std::string, HFONT> m_Fonts;

public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	void Begin();
	void End();

	//ͼԪ����
	void DrawDot(int x, int y, int c = RGB(0, 0, 0));
	void DrawLine(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawRectangle1(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawRectangle2(int x1, int y1, int x2, int y2, int pc = RGB(0, 0, 0), int bc = RGB(0xff, 0xff, 0xff));
	void DrawEllipse1(int x1, int y1, int x2, int y2, int c = RGB(0, 0, 0));
	void DrawEllipse2(int x1, int y1, int x2, int y2, int pc = RGB(0, 0, 0), int bc = RGB(0xff, 0xff, 0xff));

	//λͼ����
	bool LoadBmp(const char* fn);
	int LoadDirectory(const char* dn);
	bool ReleaseBmp(const char* fn);
	bool GetBmpWH(const char* fn, int* w, int* h);
	bool DrawBmp1(
		const char* fn,
		int sx, int sy, int sw, int sh, //Դ����
		int dx, int dy, int dw, int dh, //Ŀ�����
		int m = _MIRROR_NONE); //����
	bool DrawBmp2(
		const char* fn,
		int sx, int sy, int sw, int sh, //Դ����
		int dx, int dy, int dw, int dh, //Ŀ�����
		int tc = RGB(0, 255, 0), //͸��ɫ
		int m = _MIRROR_NONE); //����

	//���ֻ���
	bool LoadFont(
		int w, //��
		int h, //��
		int we, //��ϸ
		bool i, //�Ƿ�Ϊб��
		bool u, //�Ƿ���»���
		bool s, //�Ƿ����Խ��
		const char* f, //�������
		const char* id); //id��
	bool ReleaseFont(const char* id);
	bool DrawText1(
		const char* id, //����id��
		int x, int y, //�����������Ͻ�����
		const char* t, //�ַ���
		int c = RGB(0, 0, 0)); //��ɫ
	bool DrawText2( //���Ͻǻ���
		const char* id, //����id��
		int x, int y, int w, int h, //���־���
		const char* t, //�ַ���
		int c = RGB(0, 0, 0)); //��ɫ
	bool DrawText3( //���л���
		const char* id, //����id��
		int x, int y, int w, int h, //���־���
		const char* t, //�ַ���
		int c = RGB(0, 0, 0)); //��ɫ
};

#endif