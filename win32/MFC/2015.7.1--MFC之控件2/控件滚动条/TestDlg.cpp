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
	DDX_Control(pDX, IDC_SCROLLBAR1, hs1);
	DDX_Control(pDX, IDC_SCROLLBAR3, vs1);
	DDX_Control(pDX, IDC_SCROLLBAR2, hs2);
	DDX_Control(pDX, IDC_SCROLLBAR4, vs2);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

void CTestDlg::f()
{
	int pos[]
	=
	{
		hs1.GetScrollPos(),
		vs1.GetScrollPos(),
		hs2.GetScrollPos(),
		vs2.GetScrollPos(),
		GetScrollPos(SB_HORZ),
		GetScrollPos(SB_VERT)
	};
	CString s;
	s.Format(
		"ˮƽ1(0-%d-5)����ֱ1(0-%d-7)��ˮƽ2(0-%d-9)����ֱ2(0-%d-11)��ˮƽ3(0-%d-13)����ֱ3(0-%d-15)",
		pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]);
	SetWindowTextA(s.GetString());
}

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);

	//���ù�������Χ
	hs1.SetScrollRange(0, 5); //CScrollBar::SetScrollRange
	vs1.SetScrollRange(0, 7);
	hs2.SetScrollRange(0, 9);
	vs2.SetScrollRange(0, 11);
	SetScrollRange(SB_HORZ, 0, 13); //CWnd::SetScrollRange
	SetScrollRange(SB_VERT, 0, 15);

	//���ù�����λ��
	hs1.SetScrollPos(1); //CScrollBar::SetScrollPos
	vs1.SetScrollPos(2);
	hs2.SetScrollPos(3);
	vs2.SetScrollPos(4);
	SetScrollPos(SB_HORZ, 5); //CWnd::SetScrollPos
	SetScrollPos(SB_VERT, 6);

	f();

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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����Ƿ��Ĺ���������ôpScrollBar�ᱻ����Ϊ0�������
//�ؼ���������ôpScrollBar�ᱻ���ûᴥ������Ϣ�Ŀؼ�����
//���ĵ�ַ
void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int pos;
	if (pScrollBar)
		pos = pScrollBar->GetScrollPos();
	else
		pos = GetScrollPos(SB_HORZ);

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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK :
		{
			pos = nPos;
			break;
		}
	}

	if (pScrollBar)
		pScrollBar->SetScrollPos(pos);
	else
		SetScrollPos(SB_HORZ, pos);

	f();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos;
	if (pScrollBar)
		pos = pScrollBar->GetScrollPos();
	else
		pos = GetScrollPos(SB_VERT);

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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK :
		{
			pos = nPos;
			break;
		}
	}

	if (pScrollBar)
		pScrollBar->SetScrollPos(pos);
	else
		SetScrollPos(SB_VERT, pos);

	f();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
