// 2Dlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include <string>
#include <direct.h>
// CMy2Dlg �Ի���
class CMy2Dlg : public CDialog
{
// ����
public:
	CMy2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY2_DIALOG };

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
	CScrollBar hs;
	char work_dir[256];
	std::vector<CString> v;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	afx_msg void OnBnClickedButton1();
};
