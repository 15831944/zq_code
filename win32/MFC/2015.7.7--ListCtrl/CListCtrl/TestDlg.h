// TestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


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
	CListCtrl lc;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnDropdownCombo1();
	CComboBox cb;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};

//01)���
//{
//	01)LVS_EX_GRIDLINES��������߷��
//}
//02)�����Ϣ
//{
//	01)LVN_COLUMNCLICK���а���
//	02)NM_CLICK�������
//}
//03)��ؽṹ��
//{
//	01)POSITION
//	02)LVHITTESTINFO
//}
//04)��غ���
//{
//	01)SetExtendedStyle
//	02)InsertColumn��������
//	03)SetColumnWidth�������п���λ�����أ�
//	04)GetColumnWidth���õ��п�
//	05)InsertItem������һ�е�����
//	06)SetItemText������ָ������ָ���е��ַ���
//	07)GetItemText���õ�ָ������ָ���е��ַ���
//	08)GetItemPosition���õ�ָ���е����Ͻ�����
//	09)GetItemRect���õ�ָ���еľ���
//	10)DeleteItem��ɾ��ָ����
//	11)DeleteAllItems�����
//	12)GetItemCount���õ���ǰ������
//	13)GetSelectedCount���õ�ѡ����е�����
//	14)GetFirstSelectedItemPosition���õ����ѡ�����
//	15)GetNextSelectedItem���õ���һ��ѡ�����
//	16)SubItemHitTest���������
//}