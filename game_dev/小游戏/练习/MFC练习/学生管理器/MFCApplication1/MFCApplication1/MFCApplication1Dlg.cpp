
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "dlg1.h"

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
	DDX_Control(pDX, IDC_LIST1, lc);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCApplication1Dlg::OnNMClickList1)
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

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	erase_hang = -1;

	lc.InsertColumn(0, L"ѧ��");
	lc.InsertColumn(1, L"����");
	lc.InsertColumn(2, L"�Ա�");
	lc.InsertColumn(3, L"����");
	for (int i = 0; i < 4; ++i)
		lc.SetColumnWidth(i, 130);

	//���ô�����ߵ���չ���
	lc.SetExtendedStyle(LVS_EX_GRIDLINES);

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



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	CFileDialog fd(
		TRUE,
		0,
		0,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"�����ļ� | *.*",
		this,
		0);

	int ic;

	if (IDOK == fd.DoModal())
	{
		CString s1 = fd.GetPathName();
		FILE* pf = NULL;
		_wfopen_s(&pf, s1.GetString(), L"rb");
		fseek(pf, 0, SEEK_END);
		int fs = ftell(pf);
		rewind(pf);
		char* buf = new char[fs + 1];
		char* p = buf;
		fread(buf, 1, fs, pf);
		rewind(pf);
		fread(&ic, 1, sizeof(int), pf);
		int k = 0;
		for (int i = 0; i < ic; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				char a[32] = {};
				for (;  a[k] = p[k]; ++k)
					;
				CString s;
				fread(a, 1, strlen(a) + 1, pf);
				s.Format(L"%s", a);
				//lc.SetItemText(i,j,L"1");
				//�����0�е����λ��
				if (j == 0)
					lc.InsertItem(i, s.GetString());
				else
					lc.SetItemText(i, j, s.GetString());
			}
		}
		fclose(pf);
		delete[] buf;
	}
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	CFileDialog fd(
		FALSE,
		0,
		0,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"�����ļ� | *.*",
		this,
		0);

	int ic = lc.GetItemCount();

	if (IDOK == fd.DoModal())
	{
		CString s1 = fd.GetPathName();
		FILE* pf = NULL;
		_wfopen_s(&pf, s1.GetString(), L"wb");
		fwrite(&ic, 1, sizeof(int), pf);
		for (int i = 0; i < ic; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				CString s;
				s = lc.GetItemText(i, j);
				fwrite(s.GetString(), 1, s.GetLength() + 1, pf);
			}
		}
		fclose(pf);
	}
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	dlg1 d;
	d.add = true;
	if (IDOK == d.DoModal())
	{
		/*
		STUDENT stu;
		stu.age = d.stu.age;
		stu.id = d.stu.id;
		stu.name = d.stu.name;
		stu.sex = stu.sex;
		v_stu.push_back(stu);*/
	}
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	if (erase_hang == -1)
	{
		MessageBox(L"��ǰû��ѡ��Ҫɾ�������ݣ�");
		return;
	}
	if (IDYES == MessageBox(L"�Ƿ�ɾ����", L"��ʾ", MB_YESNO))
		lc.DeleteItem(erase_hang);
	erase_hang = -1;
}


void CMFCApplication1Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//pNMLV->ptAction���ǵ�ǰ�����λ��
	LVHITTESTINFO lh;
	lh.pt = pNMItemActivate->ptAction;
	lc.SubItemHitTest(&lh);

	int ic = lc.GetItemCount();
	dlg1 d;
	d.hang = lh.iItem;
	d.lie = lh.iSubItem;
	//ע��������������ֵ��еĵ�0�еĿհײ���Ҳ��
	//����iItemΪ-1����Ȼ���ǿ���ͨ���Լ�����GetItemRect
	//����GetItemPosition�����ж�
	if (lh.iItem == -1)
	{
		//�����˵�0��
		if (lh.iSubItem == 0)
		{
			int i;
			for (i = 0; i < lc.GetItemCount(); ++i)
			{
				POINT p, q;
				lc.GetItemPosition(i, &p);
				lc.GetItemPosition(i + 1, &q);
				if (lh.pt.y >= p.y && lh.pt.y < q.y)
					break;
			}
			if (i < lc.GetItemCount())
			{
				d.add = false;
				d.hang = i;
				d.lie = 0;
				if (IDOK == d.DoModal())
				{
				
				}
			}
			return;
		}
		return;
	}
	erase_hang = lh.iItem;
	d.add = false;
	if (IDOK == d.DoModal())
	{
		
	}
}
