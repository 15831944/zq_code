// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "Register.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "ProtocolTranslate.h"
// CRegister �Ի���

IMPLEMENT_DYNAMIC(CRegister, CDialog)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CRegister::IDD, pParent)
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ID);
	DDX_Control(pDX, IDC_EDIT2, m_Password);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
	DDX_Control(pDX, IDB_RG, m_RG);
	DDX_Control(pDX, IDB_CL, m_CL);
}


BEGIN_MESSAGE_MAP(CRegister, CDialog)
	ON_BN_CLICKED(IDOK, &CRegister::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegister::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDB_RG, &CRegister::OnBnClickedRg)
	ON_BN_CLICKED(IDB_CL, &CRegister::OnBnClickedCl)
END_MESSAGE_MAP()


// CRegister ��Ϣ�������

void CRegister::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	g_TcpClient.Disconnect();
	CDialog::OnCancel();
}

void CRegister::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	g_TcpClient.Disconnect();
	CDialog::OnOK();
}

void CRegister::OnBnClickedOk()
{
}

void CRegister::OnBnClickedCancel()
{
	
}

void CRegister::OnTimer(UINT_PTR nIDEvent)
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

				Register(id.GetString(),pw.GetString(),g_TcpClient);
				break;
			}
		case _CNE_CONNECT_FAIL:
			{
				MessageBox("����ʧ�ܣ�");
				m_ID.EnableWindow(TRUE);
				m_Password.EnableWindow(TRUE);
				m_IP.EnableWindow(TRUE);
				m_RG.EnableWindow(TRUE);
				m_CL.EnableWindow(TRUE);
				break;
			}
		case _CNE_DATA:
			{
				_PROTOCOL* xy = (_PROTOCOL*)ne.data;
				switch (xy->type)
				{
				case DL_SC_ZC_FAIL:
					{
						MessageBox("�˺��Ѿ����ڣ�");
						m_ID.EnableWindow(TRUE);
						m_Password.EnableWindow(TRUE);
						m_IP.EnableWindow(TRUE);
						m_RG.EnableWindow(TRUE);
						m_CL.EnableWindow(TRUE);
						break;
					}
				case DL_SC_ZC_OK:
					{
						MessageBox("ע��ɹ���");
						this->OnOK();
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

void CRegister::OnBnClickedRg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_IP.GetWindowTextA(ip);

	this->SetTimer(0,20,0);
	if(!g_TcpClient.ConnectIP(ip.GetString(), 12345, 5, 10, 5))
		MessageBox("IP��ַ��ʽ����");
	else
	{
		m_ID.EnableWindow(FALSE);
		m_Password.EnableWindow(FALSE);
		m_IP.EnableWindow(FALSE);
		m_RG.EnableWindow(FALSE);
		m_CL.EnableWindow(FALSE);
	}
}

void CRegister::OnBnClickedCl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
