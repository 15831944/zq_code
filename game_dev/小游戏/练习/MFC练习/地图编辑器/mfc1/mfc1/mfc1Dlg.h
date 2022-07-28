
// mfc1Dlg.h : ͷ�ļ�
//
#include <string>
#pragma once

#define _GRID_W 60
#define _GRID_H 66
#define _VIEW_W 8
#define _VIEW_H 6

// Cmfc1Dlg �Ի���
class Cmfc1Dlg : public CDialogEx
{
// ����
public:
	Cmfc1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC1_DIALOG };

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
	afx_msg void OnBnClickedButton1();

	bool init;
	char* map;
	int map_w;
	int map_h;
	int hero_x;
	int hero_y;
	int world_x;
	int world_y;
	CDC bmpdc[2];
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
