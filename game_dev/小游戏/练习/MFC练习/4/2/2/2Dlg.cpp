// 2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2.h"
#include "2Dlg.h"

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


// CMy2Dlg �Ի���




CMy2Dlg::CMy2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, hs);
}

BEGIN_MESSAGE_MAP(CMy2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMy2Dlg ��Ϣ�������

BOOL CMy2Dlg::OnInitDialog()
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
	hs.SetScrollRange(0,5);
	hs.SetScrollPos(0);

	_getcwd(work_dir, 256);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy2Dlg::OnPaint()
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
		//_chdir(work_dir);
		HBITMAP hbmp ;
		for (int i = 0 ;i < (size_t)v.size(); ++i)
		{
			if (hs.GetScrollPos() == i)
			{
				hbmp = (HBITMAP)LoadImage(0,v[i].GetString(), 
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

				CDC bmpdc;

				bmpdc.CreateCompatibleDC(&dc);
				DeleteObject(bmpdc.SelectObject(hbmp));
				DeleteObject(hbmp);

				dc.BitBlt(0,0,600,400,&bmpdc,0,0,SRCCOPY);
				bmpdc.DeleteDC();
			}
		}

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CMy2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = hs.GetScrollPos();

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

	hs.SetScrollPos(pos);

	Invalidate(0);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMy2Dlg::OnBnClickedButton1()
{
	CFileDialog fd(
					TRUE,
					0,
					0,
					OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					L"λͼ�ļ�|*.bmp",
					this,
					0);

	/*wchar_t buf[1024 * 64] = {};
	fd.GetOFN().lpstrFile = buf;
	fd.GetOFN().nMaxFile = 1024 * 64;*/

	if (fd.DoModal() == IDOK)
	{
		POSITION p =fd.GetStartPosition();
		while (p)
		{
			CString s = fd.GetNextPathName(p);
			v.push_back(s);
		}
		hs.SetScrollRange(0,v.size() - 1);
		Invalidate(0);
	}

}
