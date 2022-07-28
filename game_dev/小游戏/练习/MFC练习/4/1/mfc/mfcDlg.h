
// mfcDlg.h : ͷ�ļ�
//

#pragma once
#define MAP_W 10
#define MAP_H 10

#define VIEW_W 5
#define VIEW_H 5

#define GRID_W 50
#define GRID_H 50

// CmfcDlg �Ի���
class CmfcDlg : public CDialogEx
{
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
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();

	COLORREF map[MAP_W * MAP_H];
	int hs_pos;
	int vs_pos;
	COLORREF color;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
