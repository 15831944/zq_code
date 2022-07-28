
// mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcDlg �Ի���



CmfcDlg::CmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcDlg::OnBnClickedButton1)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CmfcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CmfcDlg::OnBnClickedButton5)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CmfcDlg ��Ϣ�������

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//������
	hs_pos = 0;
	vs_pos = 0;
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(hs_pos, VIEW_W);
	((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollRange(vs_pos, VIEW_H);

	color = RGB(255, 255, 255);

	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			map[x + y * MAP_W] = RGB(255, 255, 255);
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcDlg::OnPaint()
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
		for (int y = 0; y < VIEW_H; ++y)
		{
			for (int x = 0; x < VIEW_W; ++x)
			{
				CBrush b;
				b.CreateSolidBrush(map[x + hs_pos + (vs_pos +y) * MAP_W] );
				CBrush* b0 = dc.SelectObject(&b);
				dc.Rectangle(x * GRID_W, y * GRID_H, x * GRID_W + GRID_W, y * GRID_H + GRID_H);
				b0->DeleteObject();
			}
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	color = RGB(255, 0, 0);
	CString s;
	s += "��ǰѡ����ɫ����ɫ";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	color = RGB(255, 255, 255);
	CString s;
	s += "��ǰѡ����ɫ����ɫ";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	{
						  pos = nPos;
						  break;
	}
	}

	hs_pos = pos;
	pScrollBar->SetScrollPos(hs_pos);
	InvalidateRect(0);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
	{
						  pos = nPos;
						  break;
	}
	}

	vs_pos = pos;
	pScrollBar->SetScrollPos(vs_pos);
	InvalidateRect(0);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	color = RGB(0, 255, 0);
	CString s;
	s += "��ǰѡ����ɫ����ɫ";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	color = RGB(0, 0, 255);
	CString s;
	s += "��ǰѡ����ɫ����ɫ";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	color = RGB(0, 0, 0);
	CString s;
	s += "��ǰѡ����ɫ����ɫ";
	SetWindowText(s.GetString());
}


void CmfcDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CmfcDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x >= 0 && point.x <= VIEW_W * GRID_W
		&& point.y >= 0 && point.y <= VIEW_H * GRID_H)
	{
		int x = point.x / GRID_W;
		int y = point.y / GRID_W;
		map[x + hs_pos + (y + vs_pos) * MAP_W] = color;
	}
	InvalidateRect(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
