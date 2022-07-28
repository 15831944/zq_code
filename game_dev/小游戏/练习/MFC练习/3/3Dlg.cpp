// 3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3.h"
#include "3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy3Dlg �Ի���




CMy3Dlg::CMy3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO3, &CMy3Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMy3Dlg::OnBnClickedRadio4)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMy3Dlg ��Ϣ�������

BOOL CMy3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(FALSE);

	flag = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		for(int i = 0; i < v_tx.size(); ++i)
		{
			CPen p1;
			p1.CreatePen(PS_SOLID, 1, v_tx[i].color1);
			CPen* p0 = dc.SelectObject(&p1);

			CBrush b1;
			b1.CreateSolidBrush(v_tx[i].color2);
			CBrush* b0 = dc.SelectObject(&b1);
			if (v_tx[i].juxing)
				Rectangle(dc, v_tx[i].r.left, v_tx[i].r.top,
							v_tx[i].r.right,v_tx[i].r.bottom);
			else
				Ellipse(dc, v_tx[i].r.left, v_tx[i].r.top,
							v_tx[i].r.right, v_tx[i].r.bottom);
			p0->DeleteObject();
			b0->DeleteObject();
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMy3Dlg::OnBnClickedButton2()
{
	if (((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck())
	{
		client_w = 640;
		client_h = 480;
	}
	else if (((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck())
	{
		client_w = 800;
		client_h = 600;
	}
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);

	RECT r =
	{
		(sw - client_w ) / 2,
		(sh - client_h ) / 2,
		r.left + client_w ,
		r.top + client_h 
	};
	CalcWindowRect(&r);
	MoveWindow(&r);

	int id[] = 
		{
			IDC_RADIO1,IDC_RADIO2,IDC_RADIO3,IDC_RADIO4,IDC_BUTTON2,
			IDC_CHECK3,IDC_CHECK2,IDC_CHECK1
		};
	for (int i = 0; i < sizeof(id) / sizeof(id[0]); ++i)
	{
		((CButton*)GetDlgItem(id[i]))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(id[i]))->ShowWindow(FALSE);
	}
	flag = true;
}

void CMy3Dlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);

}

void CMy3Dlg::OnBnClickedRadio4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		((CButton*)GetDlgItem(IDC_BUTTON2))->EnableWindow(TRUE);

}

void CMy3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (flag)
	{
		_TX tx;
		int sj = 20;
		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())	
			sj = rand() % 20 + 1;
		tx.r.left = point.x - sj;
		tx.r.top = point.y - sj;
		tx.r.right = point.x + sj;
		tx.r.bottom = point.y + sj;
		tx.color1 = RGB(0, 0, 0);
		if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
			tx.color1 = RGB(rand() % 255, rand() % 255, rand() % 255);
		tx.color2 = RGB(255, 255, 255);
		if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
			tx.color2 = RGB(rand() % 255, rand() % 255, rand() % 255);
		if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
			tx.juxing = true;
		else if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck())
			tx.juxing = false;

		v_tx.push_back(tx);
		
		InvalidateRect(0);
	}
	CDialog::OnLButtonDown(nFlags, point);
}
