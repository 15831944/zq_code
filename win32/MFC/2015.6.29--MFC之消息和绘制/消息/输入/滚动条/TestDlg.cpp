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
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
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

	//�����������������
	//1�����ڷ��Ĺ�������ͨ��ModifyStyle�����
	//2���ؼ���������ͨ���϶��ؼ��������������

	//�޸Ĵ��ڷ��
	ModifyStyle(
		0, //Ҫȥ���Ĵ��ڷ��
		WS_HSCROLL | WS_VSCROLL); //Ҫ��ӵĴ��ڷ��

	//��ν���������䱾���Ϻ����ǵĴ�����ʾ����û���κ�
	//��ϵ����ֻ���ṩ��һ����Χ��min,max���Լ�һ����
	//�����Χ�б仯�ĵ�ǰֵpos�����pos�ı仯����ͨ��
	//��������Ϣ��ȷ����ֻ�������ǳ���������ͨ�����pos
	//��ȷ�����ǻ���ʱ���x,yλ�ã��������Ǵ����ӿڵ�
	//��ʽ������������������ͼ��12 X 6��
	//������������������������
	//������������������������
	//������������������������
	//������������������������
	//������������������������
	//������������������������
	//�����ӿڣ�6 X 4��ֻ����ʾ
	//������������
	//������������
	//������������
	//������������
	//��ô�ӿ����Ͻ��ڴ��ͼ����ķ�Χ����(0,0)��(6,2)
	//��ô��������ˮƽ��������min��max��0~6�����ô�ֱ
	//������������Ϊ0~2����ô���ǾͿ���ͨ������������
	//���ӿ����Ͻ��ڴ��ͼ�����λ�ã���һ���Ϳ���ͨ��
	//������Ͻ�λ����ȷ������Ҫ���ƴ��ͼ���ĸ�����

	//����ˮƽ��������Χ��λ��
	SetScrollRange(SB_HORZ, 0, 9);
	SetScrollPos(SB_HORZ, 0);

	//���ô�ֱ��������Χ��λ��
	SetScrollRange(SB_VERT, 0, 5);
	SetScrollPos(SB_VERT, 2);

	UpdateScroll();

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


void CTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//ֻҪ��ˮƽ�������Ͻ������룬���ᴥ����
	//��Ϣ��һ����˵����ֻ���Ĺ�������6���¼�

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

	//�������ǹ������Լ��ᴦ��ģ�����Ҳ�����Լ����
	if (pos < min)
		pos = min;
	if (pos > max)
		pos = max;

	SetScrollPos(SB_HORZ, pos);
	UpdateScroll();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTestDlg::UpdateScroll()
{
	int hmin, hmax, hpos;
	GetScrollRange(SB_HORZ, &hmin, &hmax);
	hpos = GetScrollPos(SB_HORZ);

	int vmin, vmax, vpos;
	GetScrollRange(SB_VERT, &vmin, &vmax);
	vpos = GetScrollPos(SB_VERT);

	char buf[64];
	sprintf_s(buf, 64, "ˮƽ(%d-%d-%d)����ֱ(%d-%d-%d)", hmin, hpos, hmax, vmin, vpos, vmax);
	//SetWindowTextA(buf);
}
void CTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int min, max, pos;
	GetScrollRange(SB_VERT, &min, &max);
	pos = GetScrollPos(SB_VERT);

	//��ˮƽ���������¼����з��ദ��
	switch (nSBCode)
	{
	case SB_LINEUP:
		{
			pos -= 1;
			break;
		}
	case SB_LINEDOWN:
		{
			pos += 1;
			break;
		}
	case SB_PAGEUP:
		{
			pos -= 2;
			break;
		}
	case SB_PAGEDOWN:
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

	//�������ǹ������Լ��ᴦ��ģ�����Ҳ�����Լ����
	if (pos < min)
		pos = min;
	if (pos > max)
		pos = max;

	SetScrollPos(SB_VERT, pos);
	UpdateScroll();

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
