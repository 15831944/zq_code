#pragma once
#include "afxwin.h"


// msdlg �Ի���



class msdlg : public CDialogEx
{
	DECLARE_DYNAMIC(msdlg)

public:
	msdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~msdlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	int w;
	int h;
	virtual BOOL OnInitDialog();
	CEdit e_w;
	CEdit e_h;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
};
