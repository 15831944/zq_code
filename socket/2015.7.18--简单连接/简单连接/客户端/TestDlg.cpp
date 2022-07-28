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
	DDX_Control(pDX, IDC_EDIT1, id);
	DDX_Control(pDX, IDC_EDIT2, pw);
	DDX_Control(pDX, IDC_LIST1, lb);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_WM_TIMER()
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
	SetTimer(0, 20, 0);
	lb.ShowWindow(SW_HIDE);

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


void CTestDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CTestDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CTestDlg::OnBnClickedButton1()
{
	id.GetWindowTextA(s1);
	pw.GetWindowTextA(s2);
	if (s1.GetLength() == 0 || s2.GetLength() == 0)
	{
		MessageBox("��Ϣ����Ϊ��");
		return;
	}
	act = 0; //��ʾע��
	tc.ConnectIP("192.168.1.3", 12345, 5, 10, 5);
}

void CTestDlg::OnBnClickedButton2()
{
	id.GetWindowTextA(s1);
	pw.GetWindowTextA(s2);
	if (s1.GetLength() == 0 || s2.GetLength() == 0)
	{
		MessageBox("��Ϣ����Ϊ��");
		return;
	}
	act = 1; //��ʾ��½
	tc.ConnectIP("192.168.1.3", 12345, 5, 10, 5);
}

void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	tc.Run();

	_CNET_EVENT ne;
	while (tc.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
			case _CNE_CONNECT_OK:
			{
				if (act == 0)
				{
					CS_ZC cs_zc;
					strcpy_s(cs_zc.id, 32, s1.GetString());
					strcpy_s(cs_zc.pw, 32, s2.GetString());
					tc.SendData(&cs_zc, sizeof(cs_zc));
				}
				else if (act == 1)
				{
					CS_DL cs_dl;
					strcpy_s(cs_dl.id, 32, s1.GetString());
					strcpy_s(cs_dl.pw, 32, s2.GetString());
					tc.SendData(&cs_dl, sizeof(cs_dl));
				}

				break;
			}
		case _CNE_CONNECT_FAIL:
			{
				MessageBox("����ʧ�ܣ�");
				break;
			}
		case _CNE_DATA:
			{
				_XY* xy = (_XY*)ne.data;
				switch (xy->type)
				{
				case 1:
					{
						MessageBox("û��ָ�����˺ţ�");
						break;
					}
				case 2:
					{
						MessageBox("���벻��ȷ��");
						break;
					}
				case 3:
					{
						lb.ShowWindow(SW_SHOW);
						GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
						GetDlgItem(IDC_BUTTON2)->EnableWindow(0);

						lb.AddString(s1.GetString());

						SC_DL_OK* dl_ok = (SC_DL_OK*)ne.data;
						char* p = (char*)(dl_ok + 1);
						for (int i = 0; i < dl_ok->num; ++i)
						{
							lb.AddString(p);
							p += strlen(p) + 1;
						}

						break;
					}
				case 4:
					{
						SC_NEW_CLIENT* new_client = (SC_NEW_CLIENT*)ne.data;
						lb.AddString(new_client->id);

						break;
					}
				case 6:
					{
						MessageBox("�˺��Ѿ����ڣ�");
						break;
					}
				case 7:
					{
						MessageBox("ע��ɹ���");
						break;
					}
				}

				break;
			}
		default: //���ֶϿ��¼�
			{
				Beep(500, 500);
				break;
			}
		}

		tc.ReleaseNetEvent(&ne);
	}

	CDialog::OnTimer(nIDEvent);
}
