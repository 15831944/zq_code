
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, e1);
	DDX_Control(pDX, IDC_EDIT2, e2);
	DDX_Control(pDX, IDC_LIST1, lb1);
	DDX_Control(pDX, IDC_LIST2, lb2);
	DDX_Control(pDX, IDC_COMBO1, cb3);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnEditchangeCombo1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCApplication1Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton3()
{
	CString s;
	e1.GetWindowText(s);
	if (s.GetLength() > 0)
		lb1.AddString(s);
	else
		MessageBox(L"���ݲ���Ϊ�գ�");
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	int pos = cb3.GetCurSel();
	if (pos != -1)
	{
		CString s;
		e2.GetWindowTextW(s);
		lb1.InsertString(pos, s.GetString());
	}
	else
		MessageBox(L"��ǰû��ѡ�����λ�û�������Ϊ�գ�");
}


void CMFCApplication1Dlg::OnBnClickedButton7()
{
	lb1.ResetContent();
	lb2.ResetContent();
}


void CMFCApplication1Dlg::OnCbnEditchangeCombo1()
{

}


void CMFCApplication1Dlg::OnCbnDropdownCombo1()
{
	cb3.ResetContent();
	CString s;
	for (int i = 0; i < lb1.GetCount(); ++i)
	{
		s.Format(L"%d", i);
		cb3.AddString(s);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	int pos = lb1.GetCurSel();
	if (pos != -1)
		lb1.DeleteString(pos);
	else
		MessageBox(L"ɾ��ʧ�ܣ�");
}


void CMFCApplication1Dlg::OnLbnSelchangeList1()
{
	
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	for (int i = 0; i < lb1.GetCount(); ++i)
	{
		CString s;
		lb1.GetText(i, s);
		MessageBox(s.GetString());
	}
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	int pos = lb1.GetCurSel();
	if (pos != -1)
	{
		CString s;
		lb1.GetText(pos, s);
		lb2.AddString(s);
		lb1.DeleteString(pos);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	int pos = lb2.GetCurSel();
	if (pos != -1)
	{
		CString s;
		lb2.GetText(pos, s);
		lb1.AddString(s);
		lb2.DeleteString(pos);
	}
}
