// msdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc.h"
#include "msdlg.h"
#include "afxdialogex.h"
#include "mfcDlg.h"
#include <string>


// msdlg �Ի���

IMPLEMENT_DYNAMIC(msdlg, CDialogEx)

msdlg::msdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(msdlg::IDD, pParent)
{

}

msdlg::~msdlg()
{
}

void msdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, e_w);
	DDX_Control(pDX, IDC_EDIT2, e_h);
}


BEGIN_MESSAGE_MAP(msdlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &msdlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &msdlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &msdlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// msdlg ��Ϣ�������


BOOL msdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	w = 16;
	h = 12;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void msdlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	e_w.GetWindowText(s);
	w = _wtoi(s.GetString());
	e_h.GetWindowText(s);
	h = _wtoi(s.GetString());
	s = "��͸߱�����10-30֮��";
	if (w < 10 || w > 30 || h < 10 || h > 30)
		MessageBox(s, L"��ʾ", MB_OK);
	else
	{
		CmfcDlg* p = (CmfcDlg*)GetParent();
		char* q = new char[w * h];
		memset(q, 0, w*h);
		for (int i = 0; i < (p->_MAP_W) * (p->_MAP_W); ++i)
			q[i] = (p->map)[i];
		p->_MAP_W = w;
		p->_MAP_H = h;
		delete[](p->map);
		(p->map) = q;
		((CScrollBar*)p->GetDlgItem(IDC_SCROLLBAR1))->MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
		((CScrollBar*)p->GetDlgItem(IDC_SCROLLBAR2))->MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);
		((CScrollBar*)p->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, w - _VIEW_W);
		((CScrollBar*)p->GetDlgItem(IDC_SCROLLBAR2))->SetScrollRange(0, h - _VIEW_H);
		p->InvalidateRect(0);
		CDialog::OnOK();
	}
}


void msdlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void msdlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
