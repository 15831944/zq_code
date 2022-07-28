#ifndef _IMAGE_BUTTON_H_
#define _IMAGE_BUTTON_H_

#include "TextButton.h"
#include <string>

#define _IBM_CLICKED _TBM_CLICKED

class CImageButton : public CTextButton
{
	std::string m_NoEnable;
	std::string m_CursorOut;
	std::string m_CursorInUp;
	std::string m_CursorInDown;

	int m_NoEnable_W, m_NoEnable_H;
	int m_CursorOut_W, m_CursorOut_H;
	int m_CursorInUp_W, m_CursorInUp_H;
	int m_CursorInDown_W, m_CursorInDown_H;

public:
	CImageButton(
		const char* no_enable, //δ����ʱ��ʾ��ͼ��
		const char* cursor_out, //������ⲿʱ��ʾ��ͼ��
		const char* cursor_in_up, //������ڲ�̧��ʱ��ʾ��ͼ��
		const char* cursor_in_down, //������ڲ�����ʱ��ʾ��ͼ��
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//virtual void Init(); //��ʼ��
	//virtual void Enter(); //������������
	//virtual void Quit(); //���������˳�
	//virtual void End(); //�˳�
	//virtual void OnEvent(int Event, int X, int Y); //����������¼�
	virtual void Render(bool Enable); //���
};

#endif