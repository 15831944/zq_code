// Xueji.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1.h"
#include "Xueji.h"
#include"1Dlg.h"


// Xueji �Ի���

IMPLEMENT_DYNAMIC(Xueji, CDialog)

Xueji::Xueji(CWnd* pParent /*=NULL*/)
	: CDialog(Xueji::IDD, pParent)
{

}

Xueji::~Xueji()
{
}

void Xueji::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cb1);
	DDX_Control(pDX, IDC_COMBO2, cb2);
	DDX_Control(pDX, IDC_EDIT1, ed1);
	DDX_Control(pDX, IDC_EDIT2, ed2);
}


BEGIN_MESSAGE_MAP(Xueji, CDialog)
	ON_BN_CLICKED(IDOK, &Xueji::OnBnClickedOk)
END_MESSAGE_MAP()


// Xueji ��Ϣ�������

BOOL Xueji::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	cb1.InsertString(0,"��");
	cb1.InsertString(1,"Ů");
	for (int i = 16; i <= 40; ++i)
	{
		CString s;
		s.Format("%d",i);
		cb2.InsertString(i - 16,s.GetString());
	}
	CMy1Dlg* p = (CMy1Dlg*)this->GetParent();
	if (p->isTranslate == true)
	{
		CString s[4];
		for (int i = 0; i < 4; ++i)
		{
			s[i] = p->listcont.GetItemText(p->cur_select_hang,i);
		}
		for (int i = 0; i < 4; ++i)
		{
			bool flag = false;
			if (i == p->cur_select_lie)
			{
				flag = true;
			}
			if (i == 0)
			{
				if (!flag)
					ed1.EnableWindow(FALSE);
				ed1.SetWindowTextA(s[i].GetString());
			}
			if (i == 1)
			{
				if (!flag)
					ed2.EnableWindow(FALSE);
				ed2.SetWindowTextA(s[i].GetString());
			}
			if (i == 2)
			{
				if (!flag)
					cb1.EnableWindow(FALSE);
				if (strcmp(s[2].GetString(),"��") == 0)
					cb1.SetCurSel(0);
				else 
					cb1.SetCurSel(1);
			}
			if (i == 3)
			{
				if (!flag)
					cb2.EnableWindow(FALSE);
				int pos = atoi(s[3].GetString()) - 16; 
				cb2.SetCurSel(pos);
			}
		}
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void Xueji::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMy1Dlg* p1 = (CMy1Dlg*)this->GetParent();
	if (p1->isTranslate)
	{
		CString s[4];
		ed1.GetWindowTextA(s[0]);
		if (atoi(s[0].GetString()) <= 0)
		{
			MessageBox("ѧ����Ч\nѧ�ű���Ϊ������");
			return;
		}
		ed2.GetWindowTextA(s[1]);
		if (s[1].GetLength() <= 0 || s[1].GetLength() > 31)
		{
			MessageBox("������Ч\n����ֻ��Ϊ1~31�ֽ�");
			return;	
		}
		int pos[2];
		if (cb1.GetCurSel() == -1)
		{
			MessageBox("�Ա���Ч");
			return;	
		}
		pos[0] = cb1.GetCurSel();;
		
		cb1.GetLBText(pos[0],s[2]);
		if (cb2.GetCurSel() == -1)
		{
			MessageBox("������Ч");
			return;	
		}
		pos[1] = cb2.GetCurSel();
		cb2.GetLBText(pos[1],s[3]);

		CMy1Dlg* p = (CMy1Dlg*)this->GetParent();
		int cur = atoi(s[0].GetString());
		int count = p->listcont.GetItemCount();
		for (int i = 0; i < count; ++i)
		{
			if (p->cur_select_hang == i)
				continue;
			CString s1 = p->listcont.GetItemText(i,0);
			if (atoi(s1.GetString()) == cur)
			{
				MessageBox("ѧԱ������ѧԱѧ���ظ������ʧ��");
				return;	
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			p1->listcont.SetItemText(p1->cur_select_hang,i,s[i].GetString());
		}
		p1->isTranslate = false;
	}
	else
	{
		CString s[4];
		ed1.GetWindowTextA(s[0]);
		if (atoi(s[0].GetString()) <= 0)
		{
			MessageBox("ѧ����Ч\nѧ�ű���Ϊ������");
			return;
		}
		ed2.GetWindowTextA(s[1]);
		if (s[1].GetLength() <= 0 || s[1].GetLength() > 31)
		{
			MessageBox("������Ч\n����ֻ��Ϊ1~31�ֽ�");
			return;	
		}
		int pos[2];
		if (cb1.GetCurSel() == -1)
		{
			MessageBox("�Ա���Ч");
			return;	
		}
		pos[0] = cb1.GetCurSel();
		
		cb1.GetLBText(pos[0],s[2]);
		if (cb2.GetCurSel() == -1)
		{
			MessageBox("������Ч");
			return;	
		}
		pos[1] = cb2.GetCurSel();
		cb2.GetLBText(pos[1],s[3]);

		

		CMy1Dlg* p = (CMy1Dlg*)this->GetParent();
		int cur = atoi(s[0].GetString());
		int count = p->listcont.GetItemCount();
		for (int i = 0; i < count; ++i)
		{
			CString s1 = p->listcont.GetItemText(i,0);
			if (atoi(s1.GetString()) == cur)
			{
				MessageBox("ѧԱ������ѧԱѧ���ظ������ʧ��");
				return;	
			}
		}
		p->listcont.InsertItem(count,s[0].GetString());
		for (int i = 1; i < 4; ++i)
		{
			p->listcont.SetItemText(count, i,s[i].GetString());
		}

		
		MessageBox("���ѧԱ�ɹ�");
	}
	OnOK();
}

void Xueji::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CMy1Dlg* p = (CMy1Dlg*)this->GetParent();
	p->isTranslate = false;
	CDialog::OnCancel();
}
