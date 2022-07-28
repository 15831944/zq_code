// Game.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "Game.h"
#include "GameHallDlg.h"
#include "GameSel.h"
// CGame �Ի���

#define _POKER_W 75
#define _POKER_H 111

IMPLEMENT_DYNAMIC(CGame, CDialog)

CGame::CGame(CWnd* pParent /*=NULL*/)
	:
CDialog(CGame::IDD, pParent),
showsel(false)
{

}

CGame::~CGame()
{
}

void CGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_edSendMessage);
}


BEGIN_MESSAGE_MAP(CGame, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CGame::OnBnClickedButton1)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CGame ��Ϣ�������

void CGame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(g_Player.m_PlayState == _PS_PLAYING)
	{
		CGameHallDlg* parent = (CGameHallDlg*)this->GetParent();
		dc.SetStretchBltMode(HALFTONE);
		dc.StretchBlt(0,0,500,420,&g_Table,0,0,400,300,SRCCOPY);
		dc.StretchBlt(520,10,48,48,&g_Faces[parent->m_Adversary->m_Face],0,0,48,48,SRCCOPY);
		
		dc.SetBkMode(TRANSPARENT);
		CString s = "������Ϣ��";
		dc.TextOutA(520,65,s.GetString(),s.GetLength());
		s.Format("�ǳƣ�%s",parent->m_Adversary->m_Name.c_str());
		dc.TextOutA(520,85,s.GetString(),s.GetLength());
		s.Format("���֣�%d",parent->m_Adversary->m_Score);
		dc.TextOutA(520,105,s.GetString(),s.GetLength());
		s.Format("ս����ʤ%d ƽ%d ��%d",parent->m_Adversary->m_Win,parent->m_Adversary->m_Draw,parent->m_Adversary->m_Lose);
		dc.TextOutA(520,125,s.GetString(),s.GetLength());
		

		s.Format("��ҵ�ǰ������%d",parent->m_iPlayerCurPoint);
		dc.TextOutA(25,380,s.GetString(),s.GetLength());

		int dw1 = parent->m_AdversaryPokersNum > 5 ? _POKER_W / 2 : _POKER_W;

		for(int i = 0; i < parent->m_AdversaryPokersNum; i++)
		{
			if(parent->m_AdversaryPokers[i] == -1)
				dc.Rectangle(50 + dw1 * i,50,50 + dw1 * i + _POKER_W,50 + _POKER_H);
			else
				dc.TransparentBlt(50 + dw1 * i,50,_POKER_W,_POKER_H,&g_Pokers,
				parent->m_Pokers[parent->m_AdversaryPokers[i]].tex.x,
				parent->m_Pokers[parent->m_AdversaryPokers[i]].tex.y,
				_POKER_W,_POKER_H,RGB(0,255,0));
		}

		int dw2 = parent->m_MyPokersNum > 5 ? _POKER_W / 2 : _POKER_W;

		for(int i = 0; i < parent->m_MyPokersNum; i++)
		{
			dc.TransparentBlt(50 + dw2 * i,380 - _POKER_H - 25,_POKER_W,_POKER_H,&g_Pokers,
				parent->m_Pokers[parent->m_MyPokers[i]].tex.x,
				parent->m_Pokers[parent->m_MyPokers[i]].tex.y,
				_POKER_W,_POKER_H,RGB(0,255,0));
		}

	}
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

void CGame::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CGame::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(g_Player.m_PlayState == _PS_PLAYING)
	{
		if(MessageBox("���ڴ�����Ϸ�У��˳������ж�Ϊ���ܣ��Ƿ�ȷ��Ҫ�˳���","��ʾ",MB_YESNO) == IDYES)
		{
			CS_RUN_AWAY cs_ra;
			strcpy_s(cs_ra.ID,32,g_Player.m_ID.c_str());
			g_TcpClient.SendData(&cs_ra,sizeof(cs_ra));
		}
	}
	else
		CDialog::OnCancel();
}

int CGame::game_MakeChoice()
{
	showsel = true;
	if(gs.DoModal() == IDOK)
	{
		showsel = false;
		return gs.m_iSel;
	}
	else
		return 0;
}

BOOL CGame::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CGame::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_Player.m_PlayState != _PS_PLAYING)
	{
		MessageBox("���ֶԾ��ѽ�����");
	}
	else
	{
		CString msg;
		m_edSendMessage.GetWindowTextA(msg);

		if(msg.GetLength() >= 64)
		{
			MessageBox("������Ϣ������ֻ�ܷ���64�ֽ����ڵ����֣�");
		}
		else
		{
			CS_TALK_IN_GAME cs_tig;
			strcpy_s(cs_tig.ID,32,g_Player.m_ID.c_str());
			strcpy_s(cs_tig.msg,256,msg.GetString());
			g_TcpClient.SendData(&cs_tig,sizeof(cs_tig));
			m_edSendMessage.SetWindowTextA("");
		}
	}
}

void CGame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	RECT r;
	this->GetWindowRect(&r);
	int w = r.right - r.left;
	int h = r.bottom - r.top;

	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	r.left =  (sw - w) / 2;
	r.top = (sh - h) / 2;

	this->MoveWindow(r.left,r.top,w,h);
}
