// TestDlg.h : ͷ�ļ�
//

#pragma once


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
};

//CWnd����MFC�жԴ��ڸ�������װ
//01)λ�ô�С���
//{
//	01)CalcWindowRect�����ݿͻ�����С��λ�ü��㴰�ڴ�С��λ��
//	02)MoveWindow���ƶ�����
//	03)GetClientRect���õ����ڵĿͻ�����С
//}
//02)��ʱ�����
//{
//	01)SetTimer�����ö�ʱ��
//	02)KillTimer�����ٶ�ʱ��
//}
//03)������
//{
//	01)GetWindowText���õ����ڱ���������
//	02)GetWindowTextLength���õ����ڱ��������ֵĳ���
//	03)SetWindowText�����ô��ڱ���������
//	04)MessageBox����Ϣ��
//}
//04)״̬���
//{
//	01)ShowWindow����ʾ�����ش���
//	02)EnableWindow��ʹ�����Ƿ��������
//	03)InvalidateRect�����ô�������Ч����Ͷ��һ��WM_PAINT��Ϣ��
//}
//05)������
//{
//	01)GetStyle���õ����
//	02)ModifyStyle���޸ķ��
//}
//06)�ؼ����
//{
//	01)GetDlgItem���õ��Ի�������Ŀؼ�������������ؼ����ڵĵ�ַCWnd*
//	02)GetDlgItemText���õ��Ի�������ؼ��ϵ�����
//	03)SetDlgItemText�����öԻ�������ؼ��ϵ�����
//	04)GetDlgItemInt���õ��Ի�������ؼ��ϵ��������֣����ֱ���ȫ������������������õ�����0��
//	05)SetDlgItemInt�����öԻ�������ؼ��ϵ��������֣����ֱ���ȫ����������
//}