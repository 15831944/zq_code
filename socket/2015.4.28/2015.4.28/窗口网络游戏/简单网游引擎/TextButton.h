#ifndef _TEXT_BUTTON_H_
#define _TEXT_BUTTON_H_

#include "UI.h"

#define _CURSOR_OUT 0 //������ⲿ
#define _CURSOR_IN_UP 1 //������ڲ�̧��
#define _CURSOR_IN_DOWN 2 //������ڲ�����

#define _TBM_CLICKED 100

class CTextButton : public CUI
{
protected:
	std::string m_Text; //�ı�
	int m_State; //״̬
	bool m_Down; //���±�־

public:
	CTextButton(
		const char* Text, //��ť���������
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//���ð�ť���������
	void SetText(const char Text);

	//�õ���ť���������
	const char* GetText();

	//virtual void Init(); //��ʼ��
	virtual void Enter(); //������������
	//virtual void Quit(); //���������˳�
	//virtual void End(); //�˳�
	virtual void OnEvent(int Event, int X, int Y); //����������¼�
	virtual void Render(bool Enable); //���
};

#endif