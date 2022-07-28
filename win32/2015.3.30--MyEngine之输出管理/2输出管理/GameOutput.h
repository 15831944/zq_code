#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_
#include <windows.h>
#include <string>
#include <map>

class CGameOutput
{
	HWND m_hWnd;//����
	int  m_iClientW;//�ͻ�����
	int  m_iClientH;//�ͻ�����
	HDC  m_MainDC;//���豸
	HDC  m_BackDC;//���豸
	std::map<std::string,HDC> m_Bmp;//λͼӳ���
public:
	CGameOutput(HWND hWnd);
	~CGameOutput();

	//��ʼ����,��������
	void Begin();
	void End();

	//ͼԪ��غ���
	void DrawLine(//����
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0),
		int w = 1);

	void DrawRectangle1(//�����ľ���
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0));

	void DrawRectangle2(//��ʵ�ľ���
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0,0,0),
		unsigned int bc = RGB(255,255,255));

	void DrawEllipse1(//��������Բ
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int c = RGB(0,0,0));

	void DrawEllipse2(//��ʵ����Բ
		int x1,
		int y1,
		int x2,
		int y2,
		unsigned int pc = RGB(0,0,0),
		unsigned int bc = RGB(255,255,255));

	//λͼ���
	int LoadDirectory(const char* dn);//�����ļ������������λͼ(������Ŀ¼)

	bool LoadBmp(const char* fn);//����λͼ

	bool ReleaseBmp(const char* fn);//�ͷ�λͼ

	bool DrawBmp(//����λͼ
		const char* fn,
		int dx,int dy,int dw,int dh,int sx,int sy);
};

#endif