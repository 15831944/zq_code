// TestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#define FD_SETSIZE 256
#include <Winsock2.h>
#include "afxwin.h"
#pragma comment(lib, "Ws2_32.lib")


// CTestDlg �Ի���
class CTestDlg : public CDialog
{
// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	CString nick_name;
	CIPAddressCtrl piac;
	SOCKET s_server;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox lb;
	afx_msg void OnBnClickedButton2();
	bool connect_ok;
};
