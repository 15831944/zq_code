
// mfcDlg.h : ͷ�ļ�
//

#pragma once
#define _CLIENT_H 480
#define _CLIENT_W 640

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
	CDC bmpdc;
	char* map;
	int hang;
	int lie;
	int vx;
	int vy;
public:
	void UpdateScroll();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
