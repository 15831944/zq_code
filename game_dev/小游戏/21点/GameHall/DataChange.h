#pragma once
#include "afxwin.h"
#include "GameHallDlg.h"

// CDataChange �Ի���

class CDataChange : public CDialog
{
	DECLARE_DYNAMIC(CDataChange)

public:
	CDataChange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataChange();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CEdit m_NewName;
	int m_FaceNum;
	CString m_Name;
public:
	CScrollBar m_FaceLB;
	CGameHallDlg* p;
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnBnClickedOk();
};
