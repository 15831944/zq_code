#pragma once
#include "afxwin.h"


// Xueji �Ի���

class Xueji : public CDialog
{
	DECLARE_DYNAMIC(Xueji)

public:
	Xueji(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Xueji();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox cb1;
public:
	CComboBox cb2;
public:
	CEdit ed1;
public:
	CEdit ed2;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();

protected:
	virtual void OnCancel();
};
