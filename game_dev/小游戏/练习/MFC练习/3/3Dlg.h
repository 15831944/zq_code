// 3Dlg.h : ͷ�ļ�
//

#pragma once
#include <vector>

// CMy3Dlg �Ի���
class CMy3Dlg : public CDialog
{
// ����
public:
	CMy3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY3_DIALOG };

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
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	struct _TX
	{
		bool juxing;
		RECT r;
		COLORREF color1;
		COLORREF color2;
	};
	int client_w;
	int client_h;
	bool flag;
	std::vector<_TX> v_tx;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
