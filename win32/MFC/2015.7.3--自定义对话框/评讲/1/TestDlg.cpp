// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

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


// CTestDlg �Ի���




CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, hsb);
	DDX_Control(pDX, IDC_SCROLLBAR3, vsb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
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

	//���ó�ʼ��ͼ����ɫ
	update_color(4);
	for (int i = 0; i < _MAP_S; ++i)
		map[i] = cur_color;

	//���ù�����
	hsb.MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
	vsb.MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);
	hsb.SetScrollRange(0, _MAP_W - _VIEW_W);
	hsb.SetScrollPos(0);
	vsb.SetScrollRange(0, _MAP_H - _VIEW_H);
	vsb.SetScrollPos(0);

	COLORREF color[]
	= 
	{
		RGB(255, 0, 0),
		RGB(0, 255, 0),
		RGB(0, 0, 255),
		RGB(127, 127, 127),
		RGB(255, 255, 255),
	};
	for (int i = 0; i < 5; ++i)
		b[i].CreateSolidBrush(color[i]);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
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

		//�õ��ϵĻ�ˢ
		CBrush* old_brush = dc.GetCurrentBrush();

		int vx = hsb.GetScrollPos();
		int vy = vsb.GetScrollPos();

		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int x = i % _VIEW_W;
			int y = i / _VIEW_W;
			int dx = x * _GRID_W;
			int dy = y * _GRID_H;
			char color = map[(x + vx) + (y + vy) * _MAP_W];
			dc.SelectObject(&b[color]);
			dc.Rectangle(dx, dy, dx + _GRID_W, dy + _GRID_H);
		}

		dc.SelectObject(old_brush);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnBnClickedButton1()
{
	update_color(0);
}

void CTestDlg::OnBnClickedButton2()
{
	update_color(1);
}

void CTestDlg::OnBnClickedButton3()
{
	update_color(2);
}

void CTestDlg::OnBnClickedButton4()
{
	update_color(3);
}

void CTestDlg::OnBnClickedButton5()
{
	update_color(4);
}

void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINELEFT:
	case SB_PAGELEFT:
		{
			pos -= 1;
			break;
		}
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		{
			pos += 1;
			break;
		}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINEUP:
	case SB_PAGEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			pos = nPos;
			break;
		}
	}

	pScrollBar->SetScrollPos(pos);
	InvalidateRect(0);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	for (int i = 0; i < 5; ++i)
		b[i].DeleteObject();

	CDialog::OnCancel();
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x >= 0 && point.x < _VIEW_W * _GRID_W &&
		point.y >= 0 && point.y < _VIEW_H * _GRID_H)
	{
		int vx = hsb.GetScrollPos();
		int vy = vsb.GetScrollPos();
		int cx = point.x / _GRID_W;
		int cy = point.y / _GRID_H;
		map[(cx + vx) + (cy + vy) * _MAP_W] = cur_color;
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}
