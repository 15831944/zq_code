// PTalkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "PTalkDlg.h"
#include "GameHallDlg.h"


// CPTalkDlg �Ի���

IMPLEMENT_DYNAMIC(CPTalkDlg, CDialog)

CPTalkDlg::CPTalkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPTalkDlg::IDD, pParent)
{

}

CPTalkDlg::~CPTalkDlg()
{
}

void CPTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbMessage);
	DDX_Control(pDX, IDC_EDIT1, m_lbSendMessage);
}


BEGIN_MESSAGE_MAP(CPTalkDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CPTalkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CPTalkDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPTalkDlg ��Ϣ�������

void CPTalkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CGameHallDlg* p = (CGameHallDlg*)(this->GetParent());

	CString state = player->m_Name.c_str();

	CString n = state;

	if(player->m_PlayState == _PS_NONE)
	{
		n += "�����й��С�����";
	}
	else if(player->m_PlayState == _PS_WAIT || player->m_PlayState == _PS_READY)
	{
		n.Format("%s����%d�ŷ���ȴ���ս��",state.GetString(),player->m_RoomNum);
	}
	else if(player->m_PlayState == _PS_PLAYING)
	{
		n.Format("%s����%d�ŷ��伤ս������",state.GetString(),player->m_RoomNum);
	}

	dc.SetBkMode(TRANSPARENT);
	dc.StretchBlt(30,15,48,48,&g_Faces[player->m_Face],0,0,48,48,SRCCOPY);
	dc.TextOutA(100,30,n.GetString(),(int)n.GetLength());
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

BOOL CPTalkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	parent = (CGameHallDlg*)this->GetParent();
	this->SetTimer(0,20,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPTalkDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}

void CPTalkDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s;
	m_lbSendMessage.GetWindowTextA(s);
	if(s.GetLength() > 255)
		MessageBox("��Ϣ���͹���������С��256���ֽ�");
	else if(!s.IsEmpty())
	{
		CS_PRI_TALK cs_pt;
		strcpy_s(cs_pt.ID,32,g_Player.m_ID.c_str());
		strcpy_s(cs_pt.DESID,32,player->m_ID.c_str());
		strcpy_s(cs_pt.Message,256,s.GetString());
		g_TcpClient.SendData(&cs_pt,sizeof(cs_pt));
		m_lbSendMessage.SetWindowTextA("");
	}
}

void CPTalkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(::GetAsyncKeyState(VK_RETURN) & 0x1 && this->GetActiveWindow() == this)
	{
		OnBnClickedButton1();
	}
	CDialog::OnTimer(nIDEvent);
}

void CPTalkDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CPTalkDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}
