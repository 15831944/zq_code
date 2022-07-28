// TestDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>


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

	struct _TX
	{
		POINT pos; //λ��
		char dir; //����
		COLORREF color; //��ɫ
		bool jx; //����
	};
	std::vector<_TX> tx;
	
public:
	void createTX(bool jx, CPoint point)
	{
		_TX tuxing;
		tuxing.pos.x = point.x;
		tuxing.pos.y = point.y;
		tuxing.dir = rand() % 4;
		tuxing.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		tuxing.jx = jx;
		tx.push_back(tuxing);
	}
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
