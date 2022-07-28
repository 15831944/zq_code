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
	DDX_Control(pDX, IDC_LIST1, lc);
	DDX_Control(pDX, IDC_COMBO1, cb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CTestDlg::OnCbnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CTestDlg::OnLvnColumnclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTestDlg::OnNMClickList1)
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
	lc.InsertColumn(0, "�˻�");
	lc.InsertColumn(1, "����");
	lc.InsertColumn(2, "�ǳ�");
	for (int i = 0; i < 3; ++i)
		lc.SetColumnWidth(i, 100);

	//���ô�����ߵ���չ���
	lc.SetExtendedStyle(LVS_EX_GRIDLINES);

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
	CString s[3];
	for (int i = IDC_EDIT1; i <= IDC_EDIT3; ++i)
	{
		GetDlgItemTextA(i, s[i - IDC_EDIT1]);
		if (s[i - IDC_EDIT1].GetLength() == 0)
		{
			MessageBox("��������пգ�");
			return;
		}
	}

	//�õ���ǰ��������
	int ic = lc.GetItemCount();

	//�����0�е����λ��
	lc.InsertItem(ic, s[0].GetString());

	//�����1��2��
	lc.SetItemText(ic, 1, s[1].GetString());
	lc.SetItemText(ic, 2, s[2].GetString());
}

void CTestDlg::OnCbnDropdownCombo1()
{
	cb.ResetContent();
	for (int i = 0; i < lc.GetItemCount(); ++i)
	{
		CString s;
		s.Format("%d", i);
		cb.AddString(s.GetString());
	}
}

void CTestDlg::OnBnClickedButton2()
{
	if (-1 != cb.GetCurSel())
		lc.DeleteItem(cb.GetCurSel());
	else
		MessageBox("����ѡ��Ҫɾ�����У�");
}

void CTestDlg::OnBnClickedButton3()
{
	lc.DeleteAllItems();
}

void CTestDlg::OnBnClickedButton4()
{
	if (0 == lc.GetSelectedCount())
	{
		MessageBox("��ǰû��ѡ��");
		return;
	}

	CString str1, str2;
	str1.Format("�ܹ�ѡ����%d�У��ֱ�����\n", lc.GetSelectedCount());

	//�õ���ʼλ��
	POSITION pos = lc.GetFirstSelectedItemPosition();
	while (pos)
	{
		//�õ���һ��λ�ò����ص�ǰѡ����е��±�
		int i = lc.GetNextSelectedItem(pos);

		CString s1 = lc.GetItemText(i, 0);
		CString s2 = lc.GetItemText(i, 1);
		CString s3 = lc.GetItemText(i, 2);

		str2 += s1 + " - " + s2 + " - " + s3 + "\n";
	}

	MessageBox(str2.GetString(), str1.GetString());
}

void CTestDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//C++��C�����е�ת��������ͬ��C���Ե�ת��һ����˵����
	//(����)���ʽ��������д��ʽ�ڴ����к��ѱ����֣�Ҳ����
	//�ڴ��������Է��ִ˴�������ת����������C++�н�����ת��
	//�ĳ���4���ؼ�����������Ϊ�ǹؼ��֣��������ڸ���C++
	//�������жԹؼ��ֵ���ʾ�������������ɫ���ڳ����к�����
	//��������������ת����C++�е�����ת���﷨���£�
	//XXX_cast<����>(���ʽ)��
	//static_cast����̬ת������ȫ��ͬ��C���Ե�ת��
	//dynamic_cast����̬ת������Ҫ�����ڼ̳���ϵ�½���ת��
	//const_cast��ȥ��������ת��
	//reinterpret_cast�������͵�ַ֮���ת��

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	const char* str[] = {"�˺�", "����", "�ǳ�"};
	CString s;
	s.Format("������[%s]��", str[pNMLV->iSubItem]);
	SetWindowTextA(s.GetString());
}

void CTestDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//����ת��
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	//pNMLV->ptAction���ǵ�ǰ�����λ��
	LVHITTESTINFO lh;
	lh.pt = pNMLV->ptAction;
	lc.SubItemHitTest(&lh);

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
				CString s;
				s.Format("�����˵�%d�е�%d��", i, 0);
				SetWindowTextA(s.GetString());
			}
			else
				MessageBox("����Ϊ��");
			return;
		}

		MessageBox("����Ϊ��");
		return;
	}

	//ע���0�б�������ֲ��㣬����Ҳ�����������Լ�
	//�������ж��Ƿ�����������

	CString s;
	s.Format("�����˵�%d�е�%d��", lh.iItem, lh.iSubItem);
	SetWindowTextA(s.GetString());
}
