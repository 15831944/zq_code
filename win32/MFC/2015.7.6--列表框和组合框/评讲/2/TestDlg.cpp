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
	map = 0;
	LoadBmp(&bmpdc[0], "bmp\\0.bmp");
	LoadBmp(&bmpdc[1], "bmp\\1.bmp");
	x = 0;
	y = 0;

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
		if (map)
		{
			CPaintDC dc(this);

			//����Ӣ��λ�õõ��ӿ����Ͻ�����ڴ��ͼ������
			int vx, vy;
			if (x < _VIEW_W / 2)
				vx = 0;
			else if (x >= w - _VIEW_W / 2)
				vx = w - _VIEW_W;
			else
				vx = x - _VIEW_W / 2;
			if (y < _VIEW_H / 2)
				vy = 0;
			else if (y >= h - _VIEW_H / 2)
				vy = h - _VIEW_H;
			else
				vy = y - _VIEW_H / 2;

			//�����ӿ��еĵ�ͼ
			for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
			{
				int cx = i % _VIEW_W;
				int cy = i / _VIEW_W;
				int dx = cx * _GRID_W;
				int dy = cy * _GRID_H;
				dc.BitBlt(
					dx, dy, _GRID_W, _GRID_H,
					&bmpdc[0],
					map[(cx + vx) + (cy + vy) * w] * _GRID_W,
					0,
					SRCCOPY);
			}

			//����Ӣ��
			dc.BitBlt(
				(x - vx) * _GRID_W,
				(y - vy) * _GRID_H,
				_GRID_W,
				_GRID_H,
				&bmpdc[1],
				0,0,
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


void CTestDlg::OnBnClickedButton1()
{
	CFileDialog fd(TRUE);
	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		FILE* pf = 0;
		fopen_s(&pf, s.GetString(), "rb");
		if (!pf)
		{
			MessageBox("�޷���ָ���ļ���");
			return;
		}
		fread(&w, 1, 4, pf);
		fread(&h, 1, 4, pf);
		map = new char[w * h];
		fread(map, 1, w * h, pf);
		fclose(pf);

		//��ʼ�����ڴ�С
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

		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);

		InvalidateRect(0);
	}
}

void CTestDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (map)
		delete [] map;

	bmpdc[0].DeleteDC();
	bmpdc[1].DeleteDC();

	CDialog::OnCancel();
}

BOOL CTestDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			{
				if (y > 0 && map[x + (y - 1) * w] == 0)
					y -= 1;
				break;
			}
		case VK_DOWN:
			{
				if (y < h - 1 && map[x + (y + 1) * w] == 0)
					y += 1;
				break;
			}
		case VK_LEFT:
			{
				if (x > 0 && map[(x - 1) + y * w] == 0)
					x -= 1;
				break;
			}
		case VK_RIGHT:
			{
				if (x < w - 1 && map[(x + 1) + y * w] == 0)
					x += 1;
				break;
			}
		}
		InvalidateRect(0);
	}

	return CDialog::PreTranslateMessage(pMsg);
}
