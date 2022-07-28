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
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
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

	//�̶��ͻ�����С�ĶԻ��򴰿�
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);
	RECT r
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		r.left + _CLIENT_W,
		r.top + _CLIENT_H
	};
	CalcWindowRect(&r);
	MoveWindow(&r);

	//�õ����豸
	CClientDC dc(this);

	//����λͼ��CDC�У�λͼ�ڱ�ѡ�뵽�豸�е�ʱ��ʵ���ϻ�
	//������һ�ݵ��豸�У�Ҳ����˵�豸����һ����hbmpһģһ��
	//��λͼ������������ѡ��֮�����ֱ�Ӱ�ԭ����hbmpɾ����
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[0].CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc[0].SelectObject(hbmp));
	::DeleteObject(hbmp);
	hbmp = (HBITMAP)LoadImageA(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[1].CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc[1].SelectObject(hbmp));
	::DeleteObject(hbmp);

	x = y = 0;
	left_right = true;

	SetTimer(0, 33, 0);

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
		//����ͼ�豸
		CPaintDC dc(this);

		//����λͼ
		dc.BitBlt(0, 0, _CLIENT_W, _CLIENT_H, &bmpdc[0], 0, 0, SRCCOPY);

		dc.TransparentBlt(
			x, y, 100, 100,
			&bmpdc[1],
			0, 0, 100, 100,
			RGB(0, 255, 0));

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	bmpdc[1].DeleteDC();
	bmpdc[0].DeleteDC();

	CDialog::OnCancel();
}

void CTestDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//�Ի��򴰿ڶԼ��̵���Ӧ����ɸѡ�ģ�����VK_LEFT��VK_DOWN
	//���޷���Ӧ�ģ�����Щ�ǿ�����Ӧ�ı�����ĸ�������ּ�����
	//���Եģ����Ҫ��õ�ԭʼ����Ϣ������ͨ����дPreTranslateMessage
	//���õ����е���Ϣ

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

//BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
//{
//	switch (pMsg->message)
//	{
//	case WM_KEYDOWN:
//		{
//			bool move = true;
//			switch (pMsg->wParam)
//			{
//			case VK_UP: y -= _HERO_SPEED; break;
//			case VK_DOWN: y += _HERO_SPEED; break;
//			case VK_LEFT: x -= _HERO_SPEED; break;
//			case VK_RIGHT: x += _HERO_SPEED; break;
//			default: move = false;
//			}
//			if (move)
//				InvalidateRect(0);
//			break;
//		}
//	}
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

void CTestDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (left_right)
	{
		x += 5;
		if (x >= _CLIENT_W - 100)
			left_right = false;
	}
	else
	{
		x -= 5;
		if (x < 0)
			left_right = true;
	}
	InvalidateRect(0);

	CDialog::OnTimer(nIDEvent);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	x = point.x;
	y = point.y;

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CTestDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���ò���ϵͳȥˢ�¿ͻ�������
	return TRUE;

	return CDialog::OnEraseBkgnd(pDC);
}
