// TestDlg.h : ͷ�ļ�
//

#pragma once

#include "TcpClient.h"
#include "..\\GameProtocol.h"
#include <string>
#include <map>
#include "afxcmn.h"
#include "afxwin.h"

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

	//�ͻ���
	CTcpClient tc;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetScene(bool p);
	afx_msg void OnBnClickedButton1();
	std::string m_IP, m_Nick_Name;
	CIPAddressCtrl ip_a_c;

	//��Ϸ
	char map[_GAME_MAP_S]; //��ͼ
	std::map<std::string, POINT> all_player; //��Ϸ���
	CListBox lb;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
