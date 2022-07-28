// GameSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "GameSel.h"


// CGameSel �Ի���

IMPLEMENT_DYNAMIC(CGameSel, CDialog)

CGameSel::CGameSel(CWnd* pParent /*=NULL*/)
	: CDialog(CGameSel::IDD, pParent)
{

}

CGameSel::~CGameSel()
{
}

void CGameSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameSel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameSel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGameSel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CGameSel::OnBnClickedButton4)
END_MESSAGE_MAP()


// CGameSel ��Ϣ�������

BOOL CGameSel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_iSel = _GS_CONTINUE;
	RECT r;
	this->GetWindowRect(&r);
	int w = r.right - r.left;
	int h = r.bottom - r.top;

	RECT pr;
	this->GetParent()->GetWindowRect(&pr);
	int pw = pr.right - pr.left;
	int ph = pr.bottom - pr.top;

	r.left =  pr.left + (pw - w) / 2;
	r.top = pr.top + (ph - h) / 2;

	this->MoveWindow(r.left,r.top,w,h);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CGameSel::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CGameSel::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
}

void CGameSel::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iSel = _GS_CONTINUE;
	this->OnOK();
}

void CGameSel::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iSel = _GS_STOP;
	this->OnOK();
}

void CGameSel::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_iSel = _GS_GIVEUP;
	this->OnOK();
}

void CGameSel::EndDlg()
{
	this->EndDialog(0);
}
