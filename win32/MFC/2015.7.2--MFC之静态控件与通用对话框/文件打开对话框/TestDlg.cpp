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
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
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
	_getcwd(work_dir, 256);

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
		CPaintDC dc(this);

		//���ù���Ŀ¼Ϊ֮ǰ�洢������Ĺ���Ŀ¼
		_chdir(work_dir);

		//���ʹ�þ���·����û������
		//C:\\Documents and Settings\\Administrator\\����\\2015.7.2\\�ļ��򿪶Ի���\\01.bmp
		//ʹ�����·����Ҫ�ӵ�ǰ����Ŀ¼�в���
		HBITMAP hbmp = (HBITMAP)LoadImageA(0, "01.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		CDC bmpdc;
		bmpdc.CreateCompatibleDC(&dc);
		DeleteObject(bmpdc.SelectObject(hbmp));
		DeleteObject(hbmp);

		dc.BitBlt(300, 100, 200, 200, &bmpdc, 0, 0, SRCCOPY);

		bmpdc.DeleteDC();

		char buf[256];
		SetWindowTextA(_getcwd(buf, 256));

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�Ի����Ϊ����
//1��ģʽ�Ի������ֶԻ��򲻹رյĻ�����
//   �ĸ��������޷���Ӧ���ǵ�����ģ�MFC
//   �е�ģʽ�Ի�������϶�����DoModal����
//   ��������ʾ�ģ��ʺ����ڷ������ɵ����
//   ��ʹ��
//2����ģʽ�Ի������ֶԻ���ر���񶼲�Ӱ
//   �����ĸ�������Ӧ���ǵ����룬��ģʽ�Ի�
//   ��һ�����Ƕ���ShowWindow����ʾ��������
//ͨ�öԻ����У��ļ��򿪹رա���ɫ�������
//�Ի�����ģʽ�Ի��򣬵����ı������滻�Ի�
//���Ƿ�ģʽ�Ի���

void CTestDlg::OnBnClickedButton1()
{
	//�������ʽ������дTRUE��ʾ�ļ��򿪶Ի���
	//�������ʽ������дFALSE��ʾ�ļ����Ի���
	CFileDialog fd(TRUE);

	//����ǰ�[��]�رնԻ���ģ���ôDoMal����
	//�ķ���ֵ����IDOK������ǰ�[ȡ��]�رնԻ���
	//�Ļ���ô����ֵ��IDCANCEL
	if (IDOK == fd.DoModal())
	{
		//GetPathName���Եõ�����ѡ���
		//�ļ�������·����
		m_SrcFileName = fd.GetPathName();

		SetWindowTextA(m_SrcFileName.GetString());

		//�ڵõ����ļ���·����������һ��
		//�Ϳ���ͨ��fopen��fclose�������ļ�
		//���������������ļ���
	}
}

void CTestDlg::OnBnClickedButton2()
{
	if (m_SrcFileName.GetLength() > 0)
	{
		CFileDialog fd(FALSE);
		if (IDOK == fd.DoModal())
		{
			CString DestFile = fd.GetPathName();
			
			FILE* pf = 0;
			fopen_s(&pf, m_SrcFileName.GetString(), "rb");
			fseek(pf, 0, SEEK_END);
			int fs = ftell(pf);
			rewind(pf);
			char* fd = new char[fs];
			fread(fd, 1, fs, pf);
			fclose(pf); //�Ͽ��˳����е����ָ���Ӳ��������Ǹ��ļ�����ϵ

			fopen_s(&pf, DestFile.GetString(), "wb");
			fwrite(fd, 1, fs, pf);
			fclose(pf);

			MessageBox("���ݳɹ���");
		}
	}
	else
		MessageBox("������ѡ��Ҫ���ݵ��ļ���");
}

void CTestDlg::OnBnClickedButton3()
{
	//OFN_HIDEREADONLY������ֻ����ѡ��
	//OFN_OVERWRITEPROMPT�����Ҫ������������ʾ���ļ������ʹ�ã�
	//OFN_ALLOWMULTISELECT�������ѡ
	//OFN_FILEMUSTEXIST���ļ��������
	//OFN_FORCESHOWHIDDEN��ǿ����ʾ�����ļ���

	CFileDialog fd(
		FALSE, //TRUEΪ�򿪡�FALSE�ر�
		0, //Ĭ�ϵ��ļ���չ��
		0, //Ĭ�ϵ��ļ���
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, //���
		0, //�ļ����͹����ַ���
		this, //������
		0); //δʹ��

	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		SetWindowTextA(s.GetString());
	}

	//Windows�кܶຯ��������ʱû��ʹ�õĲ��������
	//��ʵ�Ǻܸ�������ƣ��Ժ��������Ҫ��չ���ܣ���
	//ô��Щ�������ܾ������ˣ��ϸ���˵һ����������ֻ
	//��Ҫһ��voidָ����Ϊ��ʽ��������
	//int f1(int a, int b, int c)
	//{
	//	return a + b + c;
	//}
	//struct _����
	//{
	//	int a, b, c;
	//};
	//int f2(void* p)
	//{
	//	_����* q = (_����*)p;
	//	return q->a + q->b + q->c;
	//}
}

void CTestDlg::OnBnClickedButton4()
{
	CFileDialog fd(
		FALSE, //TRUEΪ�򿪡�FALSE�ر�
		0, //Ĭ�ϵ��ļ���չ��
		0, //Ĭ�ϵ��ļ���
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, //���
		"λͼ�ļ�|*.bmp|JPEG�ļ�|*.jpg|�����ļ�|*.*||", //"����1|*.XXX|����2|*.XXX||"
		this, //������
		0); //δʹ��

	if (IDOK == fd.DoModal())
	{
		CString s = fd.GetPathName();
		SetWindowTextA(s.GetString());
	}
}

void CTestDlg::OnBnClickedButton5()
{
	CFileDialog fd(
		TRUE, //TRUEΪ�򿪡�FALSE�ر�
		0, //Ĭ�ϵ��ļ���չ��
		0, //Ĭ�ϵ��ļ���
		OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		0,
		this, //������
		0); //δʹ��

	//�ļ��򿪶Ի��������Ҫʹ�ö��ļ���Ҫע�����ڲ�
	//�洢�����ļ����ַ����������С�����Ļ���������
	//�Դ洢����ѡ��������ļ����ƣ���������ַ�����
	//��С��MAX_PATH����260��������ֻ���Լ��������Ĵ�
	//���ռ��������
	char buf[1024 * 64] = {};
	fd.GetOFN().lpstrFile = buf;
	fd.GetOFN().nMaxFile = 1024 * 64;

	if (fd.DoModal() == IDOK)
	{
		std::vector<std::string> v;

		//�õ���ʼ��λ��
		POSITION p = fd.GetStartPosition();
		while (p)
		{
			//����λ�õõ��ļ�������������һ��λ�ã���
			//��һ��λ��Ϊ0���ʾ��ǰû���ļ���
			CString s = fd.GetNextPathName(p);
	
			//�������
			v.push_back(std::string(s.GetString()));
		}

		std::string s;
		for (int i = 0; i < v.size(); ++i)
		{
			s += v[i];
			s += "\r\n";
		}
		MessageBoxA(s.c_str());
	}
}

//�ļ��򿪶Ի�����޸ĵ�ǰ����Ĺ���·���ģ�һ����˵
//��ǰ����Ĺ���·��������exe�ļ����ڵ�Ŀ¼�����ǿ���
//ͨ������ĺ������ж�ȡ������
//char* _getcwd(char *buffer, int maxlen);
//int _chdir(const char *dirname);


void CTestDlg::OnBnClickedButton6()
{
	//���ڴ洢Ŀ¼·�����ַ�����
	char d[MAX_PATH];

	BROWSEINFO bi = {};
	bi.hwndOwner = m_hWnd;   
	bi.pszDisplayName = d;
	bi.lpszTitle = "Ŀ¼�򿪶Ի���ı��⣡��";   
	bi.ulFlags = BIF_RETURNONLYFSDIRS;     

	//Ŀ¼�򿪶Ի���
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl)   
	{   
		//�õ�Ŀ¼·��
		SHGetPathFromIDList(pidl, d);

		MessageBox(d);
	}
}
