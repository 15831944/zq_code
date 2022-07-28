// dlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "dlg1.h"


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
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_EDIT2, e2);
}


BEGIN_MESSAGE_MAP(dlg1, CDialog)
	ON_BN_CLICKED(IDOK, &dlg1::OnBnClickedOk)
END_MESSAGE_MAP()


// dlg1 ��Ϣ�������

void dlg1::OnBnClickedOk()
{
	CString s[2];
	e1.GetWindowTextA(s[0]);
	e2.GetWindowTextA(s[1]);
	if (s[0].GetLength() == 0 || s[1].GetLength() == 0)
	{
		MessageBox("������û����д��");
		return;
	}
	w = atoi(s[0].GetString());
	h = atoi(s[1].GetString());
	if (w == 0 || h == 0)
	{
		MessageBox("�����д���");
		return;
	}
	if (w < 8 || w > 32 || h < 6 || h > 24)
	{
		MessageBox("���ݳ�����Χ��");
		return;
	}

	OnOK();
}

BOOL dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	e1.SetWindowTextA("���8~32");
	e2.SetWindowTextA("���6~24");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
