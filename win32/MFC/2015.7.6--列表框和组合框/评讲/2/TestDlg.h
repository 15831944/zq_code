// TestDlg.h : ͷ�ļ�
//

#pragma once

#define _GRID_W 60 
#define _GRID_H 66
#define _VIEW_W 7
#define _VIEW_H 5
#define _CLIENT_W (_GRID_W * _VIEW_W)
#define _CLIENT_H (_GRID_H * _VIEW_H)

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
public:
	afx_msg void OnBnClickedButton1();

	int w, h;
	char* map;

	CDC bmpdc[2];

	void LoadBmp(CDC* bmpdc, const char* fn)
	{
		HBITMAP hbmp = (HBITMAP)::LoadImageA(0, fn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hbmp)
			return;
		CClientDC dc(this);
		bmpdc->CreateCompatibleDC(&dc);
		DeleteObject(bmpdc->SelectObject(hbmp));
		DeleteObject(hbmp);
	}

protected:
	virtual void OnOK();
	virtual void OnCancel();

	int x, y;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
