// TestDlg.h : ͷ�ļ�
//

#pragma once
#include "dlg1.h"
#include <vector>
#include "afxwin.h"

// CTestDlg �Ի���
class CTestDlg : public CDialog
{
	//��ģʽ�Ի�������DoMadol���г���������
	//ģʽ�Ի���������һ���ֲ�������һ������
	//�������ĺ�������ôģʽ�Ի������ʧ�ˣ�Ҳ
	//����ģʽ�Ի�����������ڽ�����
	
	//��ģʽ�Ի������������Ӧ�ú����Ի���һ��
	//����ֱ�Ӷ����ģʽ�Ի��������Ϊ���Ի���
	//��ĳ�Ա������Ȼ�������Create����������
	//����Ի�����ShowWindow����ʾ����������
	//ע������Ƿ�ģʽ�Ի�����ôEndDialog�Ĺ�
	//��Ҳ����������OnOK��OnCancel�о͵�����EndDialog�ģ�
	dlg1 d;

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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	struct TX
	{
		bool jx;
		POINT pos;
	};
	std::vector<TX> tx;
	afx_msg void OnEnChangeEdit1();
	CEdit e;
};
