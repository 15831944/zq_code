// fmsdlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc.h"
#include "fmsdlg.h"
#include "afxdialogex.h"


// fmsdlg �Ի���

IMPLEMENT_DYNAMIC(fmsdlg, CDialogEx)

fmsdlg::fmsdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(fmsdlg::IDD, pParent)
{

}

fmsdlg::~fmsdlg()
{
}

void fmsdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(fmsdlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// fmsdlg ��Ϣ�������


void fmsdlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 180, 66, &bmpdc, 0, 0, SRCCOPY);

}


BOOL fmsdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CClientDC dc(this);
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc.CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc.SelectObject(hbmp));
	::DeleteObject(hbmp);

	c = 0;

	CString s;
	s = "��ǰѡ��Ϊ����";
	SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void fmsdlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.y >= 0 && point.y <= 66)
	{
		CString s;
		if (point.x >= 0 && point.x <= 60)
		{
			s = "��ǰѡ��Ϊ����";
			SetWindowText(s);
			c = 0;
		}
		if (point.x >60 && point.x <= 120)
		{
			s = "��ǰѡ��Ϊ����";
			SetWindowText(s);
			c = 1;
		}
		if (point.x >120 && point.x <= 180)
		{
			s = "��ǰѡ��Ϊ���ϰ�";
			SetWindowText(s);
			c = 2;
		}
	}
	InvalidateRect(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void fmsdlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	c = -1;
	CDialogEx::OnOK();
}
