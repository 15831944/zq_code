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
	virtual BOOL OnInitDialog();

	COLORREF c;
	afx_msg void OnPaint();
	CString str;
protected:
	virtual void OnOK();
public:
	CEdit e;
};
