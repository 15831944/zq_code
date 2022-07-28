// 2Dlg.h : ͷ�ļ�
//

#pragma once
#define _CLIENT_W 640
#define _CLIENT_H 480

#include <list>
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	struct OBJ
	{
		POINT p;
		int color;
		int dir;
		int flag;
	};
	std::list<OBJ> l_obj;
protected:
	virtual void OnOK();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
