// TestDlg.h : ͷ�ļ�
//

#pragma once

#define _GRID_W 64
#define _GRID_H 48
#define _VIEW_W 10
#define _VIEW_H 8
#define _MAP_W 32
#define _MAP_H 32
#define _CLIENT_W (_GRID_W * _VIEW_W) //û�м���������Ŀ�
#define _CLIENT_H (_GRID_H * _VIEW_H) //û�м���������ĸ�

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

	char map[_MAP_W * _MAP_H];
	CDC bmpdc;
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
