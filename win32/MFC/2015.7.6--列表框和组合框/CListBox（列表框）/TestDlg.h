// TestDlg.h : ͷ�ļ�
//

#pragma once
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
public:
	CListBox lb;
	afx_msg void OnBnClickedButton1();
	CEdit e1;
	CEdit e2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnLbnSelchangeList1();
};

//01)AddString������ַ���
//02)GetTextLen���õ�ָ��λ�õ��ַ����ĳ���
//03)GetText���õ�ָ��λ�õ��ַ���
//04)GetCurSel���õ���ǰ��ѡ��λ��
//05)SetCurSel�����õ�ǰ��ѡ��λ��
//06)InsertString�������ַ���
//07)GetCount���õ��ַ�������
//08)DeleteString��ɾ���ַ���
//09)ResetContent�����