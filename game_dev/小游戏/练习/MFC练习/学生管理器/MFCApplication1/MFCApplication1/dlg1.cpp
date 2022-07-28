// dlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "dlg1.h"
#include "afxdialogex.h"
#include "MFCApplication1Dlg.h"


// dlg1 �Ի���

IMPLEMENT_DYNAMIC(dlg1, CDialogEx)

dlg1::dlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(dlg1::IDD, pParent)
{

}

dlg1::~dlg1()
{
}

void dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, id_edit);
	DDX_Control(pDX, IDC_EDIT2, name_edit);
	DDX_Control(pDX, IDC_COMBO1, sex_cb);
	DDX_Control(pDX, IDC_COMBO2, age_cb);
}


BEGIN_MESSAGE_MAP(dlg1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &dlg1::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &dlg1::OnCbnDropdownCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO2, &dlg1::OnCbnDropdownCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &dlg1::OnBnClickedButton2)
END_MESSAGE_MAP()


// dlg1 ��Ϣ�������


void dlg1::OnBnClickedButton1()
{
	CMFCApplication1Dlg* p = (CMFCApplication1Dlg*)GetParent();
	if (add)
	{
		CString s[4];
		id_edit.GetWindowTextW(s[0]);
		name_edit.GetWindowTextW(s[1]);
		int pos = sex_cb.GetCurSel();
		sex_cb.GetLBText(pos, s[2]);
		pos = age_cb.GetCurSel();
		age_cb.GetLBText(pos, s[3]);
		for (int i = 0; i < 4; ++i)
		{
			if (s[i].GetLength() <= 0)
			{
				MessageBox(L"������Ϊ�գ�");
				return;
			}
		}

		stu.id = _wtoi(s[0].GetString());
		stu.name = s[1].GetString();
		stu.sex = s[2].GetString();
		stu.age = _wtoi(s[3].GetString());

		int ic = p->lc.GetItemCount();
		//�����0�е����λ��
		p->lc.InsertItem(ic, s[0].GetString());
		for (int i = 1; i < 4; ++i)
			p->lc.SetItemText(ic, i, s[i].GetString());
	}
	else
	{
		CString s;
		if (lie == 0)
		{
			id_edit.GetWindowTextW(s);
		}
		else if (lie == 1)
			name_edit.GetWindowTextW(s);
		else if (lie == 2)
		{
			int pos = sex_cb.GetCurSel();
			sex_cb.GetLBText(pos, s);
		}
		else if (lie == 3)
		{
			int pos = age_cb.GetCurSel();
			age_cb.GetLBText(pos, s);
		}
		p->lc.SetItemText(hang, lie, s.GetString());
	}

	CDialogEx::OnOK();
}


BOOL dlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!add)
	{
		if (lie == 0)
		{
			name_edit.EnableWindow(FALSE);
			age_cb.EnableWindow(FALSE);
			sex_cb.EnableWindow(FALSE);
		}
		if (lie == 1)
		{
			id_edit.EnableWindow(FALSE);
			age_cb.EnableWindow(FALSE);
			sex_cb.EnableWindow(FALSE);
		}
		if (lie == 2)
		{
			id_edit.EnableWindow(FALSE);
			age_cb.EnableWindow(FALSE);
			name_edit.EnableWindow(FALSE);
		}
		if (lie == 3)
		{
			id_edit.EnableWindow(FALSE);
			sex_cb.EnableWindow(FALSE);
			name_edit.EnableWindow(FALSE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void dlg1::OnCbnDropdownCombo1()
{
	sex_cb.ResetContent();
	CString s = L"��", s1 = L"Ů";
	sex_cb.AddString(s);
	sex_cb.AddString(s1);
}

void dlg1::OnCbnDropdownCombo2()
{
	age_cb.ResetContent();
	CString s;
	for (int i = 12; i <= 40; ++i)
	{
		s.Format(L"%d", i);
		age_cb.AddString(s.GetString());
	}
}


void dlg1::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void dlg1::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void dlg1::OnBnClickedButton2()
{
	CDialogEx::OnCancel();
}
