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
	DDX_Control(pDX, IDC_LIST1, lb);
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_EDIT2, e2);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTestDlg::OnLbnSelchangeList1)
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


void CTestDlg::OnBnClickedButton1()
{
	CString s;
	e1.GetWindowTextA(s);
	if (s.GetLength() > 0)
		lb.AddString(s.GetString());
	else
		MessageBox("���ݲ���Ϊ�գ�");
}

void CTestDlg::OnBnClickedButton2()
{
	CString s1, s2;
	e1.GetWindowTextA(s1);
	e2.GetWindowTextA(s2);
	if (s1.GetLength() > 0)
	{
		//�õ������λ�ã�atoiһ�����ֲ��ܰ�
		//�ַ���ת��Ϊ������ô�䷵��ֵ��Ϊ0

		bool bz = true;
		const char* p = s2.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s2.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}

		if (!bz)
		{
			MessageBox("λ�÷Ƿ���");
			return;
		}

		int pos = atoi(s2.GetString());

		//GetDlgItemInt
		//{
		//	GetDlgItem->GetWindowTextA(s);
		//	return atoi(s)
		//}

		//�õ���ǰ���ַ�����
		int count = lb.GetCount();

		if (pos >= 0 && pos <= count)
			lb.InsertString(pos, s1.GetString());
		else
			MessageBox("����λ�÷Ƿ���");
	}
	else
		MessageBox("���ݲ���Ϊ�գ�");
}

void CTestDlg::OnBnClickedButton3()
{
	CString s;
	e2.GetWindowTextA(s);
	if (s.GetLength() > 0)
	{
		bool bz = true;
		const char* p = s.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}
		if (!bz)
		{
			MessageBox("λ�÷Ƿ���");
			return;
		}
		
		int pos = atoi(s.GetString());
		
		//�õ���ǰ���ַ�����
		int count = lb.GetCount();

		if (pos >= 0 && pos < count)
			lb.DeleteString(pos);
		else
			MessageBox("ɾ��λ�÷Ƿ���");
	}
	else
		MessageBox("���ݲ���Ϊ�գ�");
}

void CTestDlg::OnBnClickedButton4()
{
	lb.ResetContent();
}

void CTestDlg::OnBnClickedButton5()
{
	//�õ���ǰѡ���λ�ã����û��ѡ��ͷ���-1
	int pos = lb.GetCurSel();
	if (pos != -1)
	{
		CString s;

		//�õ�ָ��λ��������ַ���
		lb.GetText(pos, s);

		//�õ�ָ��λ��������ַ�������
		int len = lb.GetTextLen(pos);

		CString s2;
		s2.Format("��%d���е����ֳ���Ϊ%d������Ϊ\n%s", pos, len, s.GetString());
		MessageBox(s2.GetString());
	}
	else
		MessageBox("û��ѡ��");
}

void CTestDlg::OnBnClickedButton6()
{
	CString s;
	e2.GetWindowTextA(s);
	if (s.GetLength() > 0)
	{
		bool bz = true;
		const char* p = s.GetString();
		if (p[0] != '+' && p[0] != '-' && (p[0] < '0' || p[0] > '9'))
			bz = false;
		if (bz)
		{
			for (int i = 1; i < s.GetLength(); ++i)
			{
				if (p[i] < '0' || p[i] > '9')
				{
					bz = false;
					break;
				}
			}
		}
		if (!bz)
		{
			MessageBox("λ�÷Ƿ���");
			return;
		}
		
		int pos = atoi(s.GetString());
		
		//�õ���ǰ���ַ�����
		int count = lb.GetCount();

		if (pos >= 0 && pos < count)
			lb.SetCurSel(pos);
		else
			MessageBox("ѡ��λ�÷Ƿ���");
	}
	else
		MessageBox("���ݲ���Ϊ�գ�");
}

void CTestDlg::OnLbnSelchangeList1()
{
	//LBN_SELCHANGE��һ��ѡ������仯�ͻᴥ������Ϣ
	//����ֻ����ͨ������������ĸı�ſ��ԣ���SetCurSel
	//�ǲ��е�
	int pos = lb.GetCurSel();
	CString s;
	s.Format("��ǰѡ����%d��", pos);
	SetWindowTextA(s.GetString());
}
