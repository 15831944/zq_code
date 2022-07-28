// 2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2.h"
#include "2Dlg.h"
#include <time.h>
#include <list>
using namespace std;

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
}

BEGIN_MESSAGE_MAP(CMy2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
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

	srand((unsigned int)time(0));
	SetTimer(0,33,0);
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
		CPaintDC dc(this);
		for(list<OBJ>::iterator i = l_obj.begin(); i != l_obj.end();)
		{
			CBrush* b0;
			if (i->flag == 0)
			{
				CBrush b;
				b.CreateSolidBrush(i->color);
				b0 = dc.SelectObject(&b);
				dc.Rectangle(i->p.x - 20,i->p.y - 20,i->p.x + 20,i->p.y + 20);
			}
			else
			{
				CBrush b;
				b.CreateSolidBrush(i->color);
				b0 = dc.SelectObject(&b);
				dc.Ellipse(i->p.x - 20,i->p.y - 20,i->p.x + 20,i->p.y + 20);
			}
			if (i->p.y <=0 || i->p.y >= _CLIENT_H
				|| i->p.x <=0 || i->p.x >= _CLIENT_W)
				i = l_obj.erase(i);
			else
				++i;
			
				b0->DeleteObject();
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	OBJ obj;
	obj.p = point;
	obj.dir = rand() % 4;
	obj.flag = rand() % 2;
	obj.color = RGB(rand() % 255,rand() % 255,rand() % 255);
	l_obj.push_back(obj);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMy2Dlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
}

void CMy2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CPaintDC dc(this);
	for(list<OBJ>::iterator i = l_obj.begin(); i != l_obj.end();++i)
	{
		switch (i->dir)
		{
		case 0:i->p.y -= 5;break;
		case 1:i->p.y += 5;break;
		case 2:i->p.x -= 5;break;
		case 3:i->p.x += 5;break;
		}
	}
	InvalidateRect(0);

	CDialog::OnTimer(nIDEvent);
}

BOOL CMy2Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return true;
	return CDialog::OnEraseBkgnd(pDC);
}
