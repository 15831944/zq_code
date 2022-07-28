
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
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
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
	//�޸Ĵ��ڷ��
	ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);

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

	//����λͼ
	CClientDC dc(this);
	HBITMAP hbmp;
	hbmp = (HBITMAP)LoadImageA(0, "0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bmpdc.CreateCompatibleDC(&dc);
	::DeleteObject(bmpdc.SelectObject(hbmp));
	::DeleteObject(hbmp);

	//��ȡ��ͼ
	FILE* pf = NULL;
	fopen_s(&pf, "Map2.txt", "rb");
	fseek(pf, 0, SEEK_END);
	int filesize = ftell(pf);
	rewind(pf);
	map = (char*)malloc(filesize + 1);
	map[filesize] = 0;
	fread(map, 1, filesize, pf);
	fclose(pf);

	hang = 1, lie = 0;
	for (int i = 0; map[i] != '\r'; ++i)
		++lie;
	for (int i = 0; i < strlen(map); ++i)
	{
		if (map[i] == '\n')
			++hang;
	}
	char* p = (char*)malloc(filesize + 1);
	char* q = p;
	int len = 0;
	for (int i = 0; i < filesize; ++i)
	{
		if (map[i] != '\r' && map[i] != '\n')
			p[len++] = map[i];
	}
	p[len] = 0;
	free(map);
	map = q;

	vx = 0;
	vy = 0;
	//ˮƽ
	SetScrollRange(SB_HORZ, 0, lie - 10);
	SetScrollPos(SB_HORZ, vx);

	//��ֱ
	SetScrollRange(SB_VERT, 0, hang - 10);
	SetScrollPos(SB_VERT, vx);
	SetTimer(0, 33, 0);
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
		//����ͼ�豸
		CPaintDC dc(this);
	//	dc.TransparentBlt(0, 0, _CLIENT_W, _CLIENT_H, &bmpdc, 64, 0,64,48, RGB(0,255,0));

		for (int i = 0; i < hang; ++i)
		{
			for (int j = 0; j < lie; ++j)
			{
				if (map[(j + vx) + (i + vy) * lie] == '0')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 0 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '1')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 1 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '2')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 2 * 64, 0, 64, 48, RGB(0, 255, 0));
				if (map[(j + vx) + (i + vy) * lie] == '3')
					dc.TransparentBlt(j * 64, i * 48, 64, 48, &bmpdc, 3 * 64, 0, 64, 48, RGB(0, 255, 0));
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

void CmfcDlg::UpdateScroll()
{

}



void CmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	InvalidateRect(0);
	CDialogEx::OnTimer(nIDEvent);
}


void CmfcDlg::OnCancel()
{
	KillTimer(0);
	bmpdc.DeleteDC();
	free(map);

	CDialogEx::OnCancel();
}


BOOL CmfcDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return true;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CmfcDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//�õ�ˮƽ�������ķ�Χ��λ��
	int min, max, pos;
	GetScrollRange(SB_HORZ, &min, &max);
	pos = GetScrollPos(SB_HORZ);

	//��ˮƽ���������¼����з��ദ��
	switch (nSBCode)
	{
	case SB_LINELEFT:
		{
				pos -= 1;
				break;
		}
	case SB_LINERIGHT:
		{
				pos += 1;
				break;
		}
	case SB_PAGELEFT:
		{
				pos -= 2;
				break;
		}
	case SB_PAGERIGHT:
		{
				pos += 2;
				break;
		}
		//�������϶����Ƿſ���nPos���ᴫ�뵱ǰ�������λ��
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
				pos = nPos;
				break;
		}
	}

	SetScrollPos(SB_HORZ, pos);
	vx = pos;

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CmfcDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	//�õ���ֱ�������ķ�Χ��λ��
	int min, max, pos;
	GetScrollRange(SB_VERT, &min, &max);
	pos = GetScrollPos(SB_VERT);

	//�Դ�ֱ���������¼����з��ദ��
	switch (nSBCode)
	{
	case SB_LINELEFT:
		{
				pos -= 1;
				break;
		}
	case SB_LINERIGHT:
		{
				pos += 1;
				break;
		}
	case SB_PAGELEFT:
		{
				pos -= 2;
				break;
		}
	case SB_PAGERIGHT:
		{
				pos += 2;
				break;
		}
		//�������϶����Ƿſ���nPos���ᴫ�뵱ǰ�������λ��
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
				pos = nPos;
				break;
		}
	}

	SetScrollPos(SB_VERT, pos);
	vy = pos;

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
