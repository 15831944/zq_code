// dlg1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
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
	DDX_Control(pDX, IDC_EDIT1, e);
}


BEGIN_MESSAGE_MAP(dlg1, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// dlg1 ��Ϣ�������

BOOL dlg1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//���ȵõ����Ի���ĵ�ַ��Ȼ��ǿתΪ
	//���Ի�����Ϳ��Է�������������
	CTestDlg* p = (CTestDlg*)GetParent();
	c = p->color;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void dlg1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CBrush b1;
	b1.CreateSolidBrush(c);
	CBrush* b0 = dc.SelectObject(&b1);

	dc.Rectangle(0, 0, 100, 100);

	dc.SelectObject(b0);
	b1.DeleteObject();
}

void dlg1::OnOK()
{
	e.GetWindowTextA(str);
	if (str.GetLength() == 0)
	{
		MessageBox("�༭����Ϊ�գ�");
		return;
	}
	else
		CDialog::OnOK();
}
