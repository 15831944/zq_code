
// mfcDlg.h : ͷ�ļ�
//
#include "fmsdlg.h"
#pragma once


#define _GRID_W 60
#define _GRID_H 66
#define _VIEW_W 8
#define _VIEW_H 6

// CmfcDlg �Ի���
class CmfcDlg : public CDialogEx
{
	fmsdlg d;
// ����
public:
	CmfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_DIALOG };

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	char* map;
	CDC bmpdc;
	int _MAP_W;
	int _MAP_H;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnCancel();
	afx_msg void OnBnClickedButton1();
};
