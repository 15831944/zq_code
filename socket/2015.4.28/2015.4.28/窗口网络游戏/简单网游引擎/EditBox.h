#ifndef _EDIT_BOX_H_
#define _EDIT_BOX_H_

#include "UI.h"

#define _EBM_CHANGE 101 //��������һ�����ı䴥������Ϣ
#define _MAX_LENGTH 1023 //�����������

class CEditBox : public CUI
{
protected:
	char m_Str[_MAX_LENGTH + 1]; //����
	int m_StrLen; //���ֳ���
	int m_Color; //��ɫ
	char m_Face[256]; //�������
	int m_Length; //�������������
	char m_FontID[32]; //���ֵ�ID��

public:
	CEditBox(
		const char* face, //�����������
		int Color, //������ɫ
		int Length, //�������������
		const char* Text, //Ĭ���Ѿ��е�����
		int X, int Y, int W, int H, bool Visible = true, bool Enable = true);

	//�õ��༭�����������
	const char* GetText();

	virtual void Init(); //��ʼ��
	//virtual void Enter(); //������������
	//virtual void Quit(); //���������˳�
	virtual void End(); //�˳�
	virtual void OnEvent(int Event, int X, int Y);
	virtual void Render(bool Enable);
};

#endif