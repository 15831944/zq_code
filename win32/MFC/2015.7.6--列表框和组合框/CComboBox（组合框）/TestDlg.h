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
	CEdit e1;
	afx_msg void OnBnClickedButton1();
	CComboBox cb1;
	CComboBox cb2;
	CComboBox cb3;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnCbnDropdownCombo4();
	CComboBox cb4;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};


//01)GetCount���õ��б���е��ַ�������
//02)GetLBTextLen���õ��б���е��ַ�������
//03)GetLBText���õ��б���е��ַ���
//04)GetCurSel���õ���ǰѡ��
//05)SetCurSel�����õ�ǰѡ��
//06)AddString������ַ���
//07)InsertString�������ַ���
//08)DeleteString��ɾ���ַ���
//09)ResetContent�����