#pragma once


// CGameSel �Ի���
#define _GS_CONTINUE  0//����
#define _GS_STOP      1//ֹͣ
#define _GS_GIVEUP    2//����

class CGameSel : public CDialog
{
	DECLARE_DYNAMIC(CGameSel)

public:
	CGameSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameSel();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int m_iSel;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	void EndDlg();
};
