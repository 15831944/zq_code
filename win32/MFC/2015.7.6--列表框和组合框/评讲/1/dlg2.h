#pragma once


// dlg2 �Ի���

class dlg2 : public CDialog
{
	DECLARE_DYNAMIC(dlg2)

public:
	dlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~dlg2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	char sel;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
