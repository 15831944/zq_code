#include "EditBox.h"
#include "GameEngine.h"
#include "Scene.h"
#include <iostream>

CEditBox::CEditBox(const char* face,
				   int Color,
				   int Length,
				   const char* Text,
				   int X, int Y, int W, int H, bool Visible, bool Enable)
				   :
CUI(X, Y, W, H, Visible, Enable)
{
	if (Text)
	{
		strcpy_s(m_Str, _MAX_LENGTH + 1, Text);
		m_StrLen = (int)strlen(m_Str);
	}
	else
	{
		m_Str[0] = 0;
		m_StrLen = 0;
	}
	m_Color = Color;
	strcpy_s(m_Face, 256, face);
	m_Length = Length;
}

const char* CEditBox::GetText()
{
	return m_Str;
}

void CEditBox::Init()
{
	//�õ�һ������ַ���������Ϊ��ǰ����������ȡ����
	m_FontID[31] = 0;
	for (int i = 0; i < 31; ++i)
		m_FontID[i] = CGameEngine::GetRandomInt('a', 'z');

	//����һ�����ַ������ֹ�����
	CGameEngine::GetGE()->GetOutput()->LoadFont(
		m_W / m_Length,
		m_H,
		400,
		false,
		false,
		false,
		m_Face,
		m_FontID);
}

void CEditBox::End()
{
	CGameEngine::GetGE()->GetOutput()->ReleaseFont(m_FontID);
}

void CEditBox::OnEvent(int Event, int X, int Y)
{
	switch (Event)
	{
	case _UIE_L_DOWN_IN:
		{
			m_Scene->SetKeyUI(m_ID.c_str());
			break;
		}
	case _UIE_L_DOWN_OUT:
		{
			//�����ǰ���̽���ؼ������Լ��ͰѼ��̽���ؼ�����Ϊ0
			if (this == m_Scene->GetKeyUI())
				m_Scene->SetKeyUI(0);
			break;
		}
	case _UIE_CHAR:
		{
			//�����˸��
			if (X == 8)
			{
				if (m_StrLen > 0)
				{
					bool db;
					for (int i = 0; i < m_StrLen; ++i)
					{
						if (IsDBCSLeadByte(m_Str[i]))
						{
							db = true;
							i += 1;
						}
						else
							db = false;
					}
					m_Str[m_StrLen -= (db ? 2 : 1)] = 0;
					m_Scene->OnUIMessage(_EBM_CHANGE, m_ID.c_str());
				}
			}
			else
			{
				//�����˫�ֽ�����
				if (Y == 1)
				{
					char* c = (char*)&X;
					if (m_StrLen + 2 <= m_Length)
					{
						m_Str[m_StrLen++] = c[0];
						m_Str[m_StrLen++] = c[1];
						m_Str[m_StrLen] = 0;
						m_Scene->OnUIMessage(_EBM_CHANGE, m_ID.c_str());
					}
				}
				else
				{
					//�ж�һ�����ֽ������Ƿ��ǿ��Դ�ӡ������
					if (m_StrLen + 1 <= m_Length && isprint(X))
					{
						m_Str[m_StrLen++] = (char)X;
						m_Str[m_StrLen] = 0;
						m_Scene->OnUIMessage(_EBM_CHANGE, m_ID.c_str());
					}
				}
			}

			break;
		}
	}
}

void CEditBox::Render(bool Enable)
{
	CGameOutput* pOutout = CGameEngine::GetGE()->GetOutput();

	//����
	if (Enable)
	{
		int brushcolor = this == m_Scene->GetKeyUI() ? RGB(255, 255, 255) : RGB(200, 200, 200);

		pOutout->DrawRectangle2(
			m_X, m_Y, m_X + m_W, m_Y + m_H,
			RGB(0, 0, 0), brushcolor);

		//��������
		pOutout->DrawText1(
			m_FontID,
			m_X, m_Y, m_Str, m_Color);
	}
	//δ����
	else
	{
		//���ƾ���
		pOutout->DrawRectangle2(
			m_X, m_Y, m_X + m_W, m_Y + m_H,
			RGB(0, 0, 0), RGB(200, 200, 200));

		//��������
		pOutout->DrawText1(
			m_FontID,
			m_X, m_Y, m_Str, RGB(100, 100, 100));
	}
}