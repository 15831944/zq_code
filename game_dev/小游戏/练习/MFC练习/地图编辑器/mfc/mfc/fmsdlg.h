#pragma once


// fmsdlg �Ի���

class fmsdlg : public CDialogEx
{
	DECLARE_DYNAMIC(fmsdlg)
	CDC bmpdc;

public:
	fmsdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~fmsdlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	char c;
	virtual void OnOK();
};
