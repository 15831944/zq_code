// TestDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>

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

	CWnd* item[8];
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton1();

	bool jx_ty;
	bool sjkg;
	bool sjhb;
	bool sjhs;
	bool flag;

	struct _TX
	{
		RECT r;
		COLORREF p, b;
	};
	std::vector<_TX> tx;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
