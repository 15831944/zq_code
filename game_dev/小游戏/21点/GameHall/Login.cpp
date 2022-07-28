// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameHall.h"
#include "Login.h"
#include "Register.h"
#include "GameHallDlg.h"
#include "ProtocolMessageDispatcher.h"
#include "DataDefine.h"

// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddr);
	DDX_Control(pDX, IDC_EDIT1, m_ID);
	DDX_Control(pDX, IDC_EDIT2, m_Password);
	DDX_Control(pDX, IDC_BUTTON1, m_Login);
	DDX_Control(pDX, IDC_BUTTON4, m_RG);
	DDX_Control(pDX, IDC_BUTTON2, m_CL);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CLogin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CLogin ��Ϣ�������

void CLogin::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CLogin::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}

void CLogin::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->OnCancel();
}

void CLogin::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegister rgdlg;
	rgdlg.DoModal();

}

void CLogin::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString id;
	m_ID.GetWindowTextA(id);

	CString pw;
	m_Password.GetWindowTextA(pw);

	if(id.GetLength() < 8 || id.GetLength() > 16)
	{
		MessageBox("�˺ų��ȱ������8����С��16");
		m_ID.SetWindowTextA("");
		m_Password.SetWindowTextA("");
		return;
	}


	for(int i = 0; i < id.GetLength(); i++)
	{
		if(id[i] < 32 || id[i] > 128)
		{
			MessageBox("�˺ź��зǷ��ַ�");
			m_ID.SetWindowTextA("");
			m_Password.SetWindowTextA("");
			return;
		}
	}

	if(pw.GetLength() < 8 || pw.GetLength() > 16)
	{
		MessageBox("���볤�ȱ������8����С��16");
		m_ID.SetWindowTextA("");
		m_Password.SetWindowTextA("");
		return;
	}


	for(int i = 0; i < pw.GetLength(); i++)
	{
		if(pw[i] < 32 || pw[i] > 128)
		{
			MessageBox("���뺬�зǷ��ַ�");
			m_ID.SetWindowTextA("");
			m_Password.SetWindowTextA("");
			return;
		}
	}

	CString ip;
	m_IpAddr.GetWindowTextA(ip);

	

	this->SetTimer(0,20,0);
	if(!g_TcpClient.ConnectIP(ip.GetString(), 12345, 5, 10, 5))
		MessageBox("IP��ַ��ʽ����");
	else
	{
		m_ID.EnableWindow(FALSE);
		m_Password.EnableWindow(FALSE);
		m_IpAddr.EnableWindow(FALSE);
		m_Login.EnableWindow(FALSE);
		m_RG.EnableWindow(FALSE);
		m_CL.EnableWindow(FALSE);
	}
}

void CLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	g_TcpClient.Run();

	_CNET_EVENT ne;
	while (g_TcpClient.GetNetEvent(&ne))
	{
		switch (ne.type)
		{
			case _CNE_CONNECT_OK:
			{
				
				CString id;
				m_ID.GetWindowTextA(id);

				CString pw;
				m_Password.GetWindowTextA(pw);

				g_Player.m_ID = id;

				Login(id.GetString(),pw.GetString(),g_TcpClient);
				break;
			}
		case _CNE_CONNECT_FAIL:
			{
				MessageBox("����ʧ�ܣ�");
				m_ID.EnableWindow(TRUE);
				m_Password.EnableWindow(TRUE);
				m_IpAddr.EnableWindow(TRUE);
				m_Login.EnableWindow(TRUE);
				m_RG.EnableWindow(TRUE);
				m_CL.EnableWindow(TRUE);
				break;
			}
		case _CNE_DATA:
			{
				_PROTOCOL* xy = (_PROTOCOL*)ne.data;
				switch (xy->type)
				{
				case DL_SC_NO_ID:
					{
						MessageBox("û��ָ�����˺ţ�");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
				case DL_SC_PW_ERROR:
					{
						MessageBox("���벻��ȷ��");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
					//��½�ɹ�
				case DL_SC_DL_OK:
					//����Ҽ���
				case DL_SC_NEW_CLIENT:
					{
						g_PMDispatcher.ProtocolRun(ne);
						this->OnOK();
						break;
					}
				case DL_SC_DL_AGAIN:
					{
						MessageBox("���˺��ѵ�¼��");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IpAddr.EnableWindow(TRUE);
						m_Login.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
				}
				break;
			}
		case _CNE_DISCONNECTED_C:
		case _CNE_DISCONNECTED_S:
				{
					Beep(500, 500);
					break;
				}
		case _CNE_DISCONNECTED_E:
			{
				KillTimer(0);
				if(MessageBox("������ʧȥ����,���򼴽��رա�","����ʧ��",MB_OK) == IDOK)
				{
					this->OnCancel();
				}
				break;
			}
		}

		g_TcpClient.ReleaseNetEvent(&ne);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_IpAddr.SetWindowTextA("127.0.0.1");
	m_ID.SetWindowTextA("aabbccdd");
	m_Password.SetWindowTextA("aabbccdd");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLogin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
