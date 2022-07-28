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

//ÿ���Ի����������Ի����У�Ĭ�Ͼ�Ϊ�Ի��������
//��ӦWM_PAINT��Ϣ�ĺ���OnPaint�����ǵ����л��ƴ���
//��Ӧ�÷���OnPaint�����У���OnPaint����������ʹ��
//CPaintDC�����л��ƣ�CPaintDC�Ĺ��졢�����оͷֱ�
//������BeginPaint��EndPaint�ˣ��������ǲ���Ҫ��ȥ
//�����������������������еĻ��ƺ���������װ��Ϊ��
//CPaintDC�ĳ�Ա�������ϸ���˵��Щ���ƺ���������CPaintDC
//�ĳ�Ա����������CPaintDC�̳���CDC�ĳ�Ա��������CDC
//���������������OnPaint������ר�õ�CPaintDC������
//һ����CClientDC�����࣬�������Ĺ���������ֱ��
//����GetDC��ReleaseDC����������
//���е�GDI���󶼱���װ��Ϊ���࣬�ֱ�����
//CPen:CreatePen
//CBrush:CreateSolidBrush��CreateHatchBrush
//CFont:CreateFont
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

		//�������ֱ���Ϊ͸��
		dc.SetBkMode(TRANSPARENT);

		//��������
		CPen p1;
		p1.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

		//������ѡ�뵽�豸
		CPen* p0 = dc.SelectObject(&p1);

		//���ƾ���
		dc.Rectangle(100, 100, 200, 200);

		//������ˢ
		CBrush b1;
		b1.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 0));

		//����ˢѡ�뵽�豸
		CBrush* b0 = dc.SelectObject(&b1);

		//������Բ
		dc.Ellipse(50, 100, 300, 150);

		//��������
		CFont f1;
		f1.CreateFontA(
			30,
			15,
			0,
			0,
			FW_HEAVY,
			false,
			false,
			false,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			"����");

		//������ѡ�뵽�豸
		CFont* f0 = dc.SelectObject(&f1);

		dc.TextOutA(0, 0, "123abc���", 10);

		//û��ѡ�뵽�豸�е�GDI�������Ǳ���
		//�ֶ��ͷţ����豸�еĶ���������豸
		//һ���ͷ�
		p0->DeleteObject();
		b0->DeleteObject();
		f0->DeleteObject();

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

