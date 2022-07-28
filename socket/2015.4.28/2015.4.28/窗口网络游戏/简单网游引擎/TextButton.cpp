#include "TextButton.h"
#include "GameEngine.h"
#include "Scene.h"

CTextButton::CTextButton(const char* Text,
						 int X, int Y, int W, int H, bool Visible, bool Enable)
						 :
CUI(X, Y, W, H, Visible, Enable),
m_Text(Text),
m_State(_CURSOR_OUT),
m_Down(false)
{}

void CTextButton::SetText(const char Text)
{
	m_Text = Text;
}

const char* CTextButton::GetText()
{
	return m_Text.c_str();
}

void CTextButton::Enter()
{
	m_State = _CURSOR_OUT;
}

void CTextButton::OnEvent(int Event, int X, int Y)
{
	switch (Event)
	{
	case _UIE_CURSOR_ENTER: //�������¼�
	case _UIE_CURSOR_MOVE_IN: //����ڲ��ƶ��¼�
		{
			m_State = m_Down ? _CURSOR_IN_DOWN : _CURSOR_IN_UP;
			break;
		}
	case _UIE_CURSOR_QUIT: //����˳��¼�
	case _UIE_CURSOR_MOVE_OUT: //����ⲿ�ƶ��¼�
		{

			m_State = m_Down ? _CURSOR_IN_UP : _CURSOR_OUT;
			break;
		}
	case _UIE_L_DOWN_IN: //����ڲ������¼�
		{
			m_State = _CURSOR_IN_DOWN; //������ڲ�����
			m_Down = true; //���±�־Ϊ��
			break;
		}
	case _UIE_L_UP_IN: //����ڲ�̧���¼�
		{
			//�����±�־Ϊ��
			if (m_Down)
			{
				m_State = _CURSOR_IN_UP; //������ڲ�̧��
				m_Down = false; //���±�־Ϊ��
				
				//֪ͨ��������ť������
				m_Scene->OnUIMessage(_TBM_CLICKED, m_ID.c_str());
			}
			
			break;
		}
	case _UIE_L_UP_OUT: //����ⲿ̧���¼�
		{
			m_State = _CURSOR_OUT; //������ⲿ
			m_Down = false; //���±�־Ϊ��
			break;
		}
	}
}

void CTextButton::Render(bool Enable)
{
	CGameOutput* output = CGameEngine::GetGE()->GetOutput();

	POINT p[3];

	if (m_State == _CURSOR_IN_DOWN)
	{
		p[0].x = m_X + 1;
		p[0].y = (m_Y + m_H - 1) - 1;

		p[1].x = m_X + 1;
		p[1].y = m_Y + 1;

		p[2].x = (m_X + m_W - 1) - 1;
		p[2].y = m_Y + 1;
	}
	else
	{
		p[0].x = (m_X + m_W - 1) - 1;
		p[0].y = m_Y + 1;

		p[1].x = (m_X + m_W - 1) - 1;
		p[1].y = (m_Y + m_H - 1) - 1;

		p[2].x = m_X + 1;
		p[2].y = (m_Y + m_H - 1) - 1;
	}

	int bc;
	int tc;

	if (Enable)
	{
		if (m_State == _CURSOR_OUT)
			bc = RGB(0x5f, 0x5f, 0x5f);
		else
			bc = RGB(0xff, 0xff, 0xff);
		tc = RGB(0x00, 0x00, 0x00);
	}
	else
	{
		bc = RGB(0x5f, 0x5f, 0x5f);
		tc = RGB(0xaf, 0xaf, 0xaf);
	}

	//���ƾ���
	output->DrawRectangle2(
		m_X, m_Y, m_X + m_W, m_Y + m_H,
		RGB(0x00, 0x00, 0x00),
		bc);

	//��������
	output->DrawText3(
		0, m_X, m_Y, m_W, m_H, m_Text.c_str(), tc);

	//������Ӱ
	output->DrawLine(p[0].x, p[0].y, p[1].x, p[1].y);
	output->DrawLine(p[1].x, p[1].y, p[2].x, p[2].y);
}