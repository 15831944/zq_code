// dlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "dlg1.h"
#include "TestDlg.h"

// dlg1 �Ի���

IMPLEMENT_DYNAMIC(dlg1, CDialog)

dlg1::dlg1(CWnd* pParent /*=NULL*/)
	: CDialog(dlg1::IDD, pParent)
{

}

dlg1::~dlg1()
{
}

void dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dlg1, CDialog)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// dlg1 ��Ϣ�������

BOOL dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	b1 = (CButton*)GetDlgItem(IDC_RADIO1);
	b1->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void dlg1::OnRButtonDown(UINT nFlags, CPoint point)
{
	CString s1;
	CWnd* p = GetParent();
	p->GetDlgItem(IDC_EDIT1)->GetWindowTextA(s1);
	
	CString s2;
	CTestDlg* q = (CTestDlg*)GetParent();
	q->e.GetWindowTextA(s2);

	MessageBox(s1.GetString(), s2.GetString());

	CDialog::OnRButtonDown(nFlags, point);
}
