#pragma once
#include "afxwin.h"


// dlg1 �Ի���

class dlg1 : public CDialog
{
	DECLARE_DYNAMIC(dlg1)

public:
	dlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~dlg1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int w, h;
	CEdit e1;
	CEdit e2;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
