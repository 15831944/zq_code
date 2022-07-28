
// mfc1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc1.h"
#include "mfc1Dlg.h"
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


// Cmfc1Dlg �Ի���



Cmfc1Dlg::Cmfc1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc1Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// Cmfc1Dlg ��Ϣ�������

BOOL Cmfc1Dlg::OnInitDialog()
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
	CClientDC dc(this);
	HBITMAP hbmp[2];
	hbmp[0] = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmp[1] = (HBITMAP)LoadImageA(0, "1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc[0].CreateCompatibleDC(&dc);
	bmpdc[1].CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc[0].SelectObject(hbmp[0]));
	::DeleteObject(bmpdc[1].SelectObject(hbmp[1]));
	::DeleteObject(hbmp[0]);
	::DeleteObject(hbmp[1]);

	hero_x = hero_y = 0;
	world_x = world_y = 0;
	init = false;

	SetTimer(0, 33, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cmfc1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmfc1Dlg::OnPaint()
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
		if (init)
		{
			CPaintDC dc(this);

			for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
			{
				int x = i % _VIEW_W;
				int y = i / _VIEW_W;
				int dx = x * _GRID_W;
				int dy = y * _GRID_H;
				char c = map[world_x + world_y * map_w];
				if (c == 0)
					dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc[0], 0, 0, SRCCOPY);
				else if (c == 1)
					dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc[0], 60, 0, SRCCOPY);
				else if (c == 2)
					dc.BitBlt(dx, dy, _GRID_W, _GRID_H, &bmpdc[0], 120, 0, SRCCOPY);
				dc.BitBlt(hero_x * _GRID_W, hero_y * _GRID_H, _GRID_W, _GRID_H, &bmpdc[1], 0, 0, SRCCOPY);
			}
			CDialogEx::OnPaint();
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmfc1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc1Dlg::OnBnClickedButton1()
{
	/*CFileDialog fd(TRUE);
	CString s;
	if (IDOK == fd.DoModal())
		s = fd.GetPathName();*/

	FILE* pf = NULL;
	fopen_s(&pf,"map.txt", "rb");
	if (!pf)
		MessageBox(L"�ļ���ʧ�ܣ�", L"��ʾ", MB_OK);
	fread(&map_w, 4, 1, pf);	
	fread(&map_h, 4, 1, pf);
	map = new char[map_w * map_h];
	for (int i = 0; i < map_h * map_w; ++i)
		fread(&map[i],1, 1, pf);
	fclose(pf);
	init = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(FALSE);
}


void Cmfc1Dlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void Cmfc1Dlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	KillTimer(0);
	delete[] map;
	DeleteObject(bmpdc[0]);
	DeleteObject(bmpdc[1]);
	CDialogEx::OnCancel();
}


void Cmfc1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	////// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	if (hero_y > 0 && hero_y <= _VIEW_H / 2)
	//		hero_y--;
	//}
	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	if (hero_y > map_h - _VIEW_H / 2 && hero_y < map_h - 1)
	//		hero_y++;
	//}
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	if (hero_x > 0 && hero_x <= _VIEW_W / 2)
	//		hero_x--;
	//	else
	//		world_x--;
	//}
	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	if (hero_x > map_h - _VIEW_H / 2 && hero_x < map_h - 1
	//		&& hero_x > 0 && hero_x < _VIEW_W / 2)
	//		hero_x++;
	//	else
	//		world_x++;
	//}
	//InvalidateRect(0);
	//CDialogEx::OnTimer(nIDEvent);
}


void Cmfc1Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'W' || nChar == 'w')
	{
		MessageBox(L"�ļ���ʧ�ܣ�", L"��ʾ", MB_OK);
	}
	if (nChar == 'S' || nChar == 's')
	{
		if (hero_y > map_h - _VIEW_H / 2 && hero_y < map_h - 1)
			hero_y++;
	}
	if (nChar == 'A' || nChar == 'a')
	{
		if (hero_x > 0 && hero_x <= _VIEW_W / 2)
			hero_x--;
		else
			world_x--;
	}
	if (nChar == 'D' || nChar == 'd')
	{
		if (hero_x > map_h - _VIEW_H / 2 && hero_x < map_h - 1
			&& hero_x > 0 && hero_x < _VIEW_W / 2)
			hero_x++;
		else
			world_x++;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}



BOOL Cmfc1Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		MessageBox(L"�ļ���ʧ�ܣ�", L"��ʾ", MB_OK);
		switch (pMsg->wParam)
		{
		case 'D':
		case 'd':
			if (::GetKeyState('W')<0)
			{
				if (hero_x > map_h - _VIEW_H / 2 && hero_x < map_h - 1
					&& hero_x > 0 && hero_x < _VIEW_W / 2)
					hero_x++;
				else
					world_x++;
			};
			break;
		}
		//InvalidateRect(0);
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
