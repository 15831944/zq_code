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
	DDX_Control(pDX, IDC_SCROLLBAR2, vsb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	LoadBmp(&bmpdc, "bmp\\0.bmp");

	//��������
	hsb.MoveWindow(0, _GRID_H * _VIEW_H, _GRID_W * _VIEW_W, ::GetSystemMetrics(SM_CYHSCROLL));
	vsb.MoveWindow(_GRID_W * _VIEW_W, 0, ::GetSystemMetrics(SM_CXVSCROLL), _GRID_H * _VIEW_H);

	//��ʼ������
	w = _INIT_MAP_W;
	h = _INIT_MAP_H;
	map = new char[w * h];
	for (int i = 0; i < w * h; ++i)
		map[i] = 0;

	//��ʼ��������
	hsb.SetScrollRange(0, w - _VIEW_W);
	hsb.SetScrollPos(0);
	vsb.SetScrollRange(0, h - _VIEW_H);
	vsb.SetScrollPos(0);

	d2.Create(MAKEINTRESOURCE(IDD_DIALOG2), this);

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

		int offsetx = hsb.GetScrollPos();
		int offsety = vsb.GetScrollPos();
		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int cx = i % _VIEW_W;
			int cy = i / _VIEW_W;
			int dx = cx * _GRID_W;
			int dy = cy * _GRID_H;
			dc.BitBlt(
				dx, dy, _GRID_W, _GRID_H,
				&bmpdc,
				map[(cx + offsetx) + (cy + offsety) * w] * _GRID_W,
				0,
				SRCCOPY);
		}

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::LoadBmp(CDC* bmpdc, const char* fn)
{
	HBITMAP hbmp = (HBITMAP)::LoadImageA(0, fn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hbmp)
		return;
	CClientDC dc(this);
	bmpdc->CreateCompatibleDC(&dc);
	DeleteObject(bmpdc->SelectObject(hbmp));
	DeleteObject(hbmp);
}
void CTestDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	delete [] map;
	bmpdc.DeleteDC();
	CDialog::OnCancel();
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

void CTestDlg::OnBnClickedButton2()
{
	dlg1 d;
	if (IDOK == d.DoModal())
	{
		w = d.w;
		h = d.h;
		delete []  map;
		map = new char[w * h];
		for (int i = 0; i < w * h; ++i)
			map[i] = 0;
	}
}

void CTestDlg::OnBnClickedButton3()
{
	d2.ShowWindow(SW_SHOW);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x >= 0 && point.x < _GRID_W * _VIEW_W && point.y >= 0 && point.y < _GRID_H * _VIEW_H)
	{
		int x = point.x / _GRID_W;
		int y = point.y / _GRID_H;
		int offsetx = hsb.GetScrollPos();
		int offsety = vsb.GetScrollPos();
		map[(x + offsetx) + (y + offsety) * w] = d2.sel;
		InvalidateRect(0);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CTestDlg::OnBnClickedButton1()
{
	CFileDialog fd(FALSE);
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		//��4�ֽ�
		//��4�ֽ�
		//��ͼ:w*h�ֽ�
		FILE* pf;
		fopen_s(&pf, s.GetString(), "wb");
		fwrite(&w, 1, 4, pf);
		fwrite(&h, 1, 4, pf);
		fwrite(map, 1, w * h, pf);
		fclose(pf);

		MessageBox("����ɹ���");
	}
}
