// GameHallDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "..\\GameProtocol\\Protocol.h"
#include "..\\GameProtocol\\LoginProtocol.h"
#include "..\\GameProtocol\\HallProtocol.h"
#include "..\\GameProtocol\\BlackJackProtocol.h"
#include <map>
#include <string>
#include "DataType.h"
#include "ProtocolTranslate.h"
#include "DataDefine.h"
#include "Game.h"

#define _POKERS_MAX        52
#define _PLAYER_MAX_POKERS  21

// CGameHallDlg �Ի���
class CGameHallDlg : public CDialog
{
// ����
public:
	CGameHallDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GAMEHALL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
// ʵ��
protected:
	HICON m_hIcon;

	CGame m_GameDlg;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lbOnlinePlayers;
	CListBox m_lbMessage;
	CEdit m_edSendMessage;
	CScrollBar m_sbRoomV;
	CStatic m_stName;
	CStatic m_stScore;
	CStatic m_stHistory;

	//��Ϸ���
	struct _POKER
	{
		int num;
		POINT tex;
	};

	_POKER m_Pokers[52];

	int m_MyPokers[_PLAYER_MAX_POKERS];
	int m_iPlayerCurPoint;
	int m_MyPokersNum;

	_PLAYER* m_Adversary;
	int m_AdversaryPokers[_PLAYER_MAX_POKERS];
	int m_AdversaryPokersNum;

protected:
	virtual void OnOK();
	virtual void OnCancel();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnBnClickedButton1();
public:
	afx_msg void OnLbnDblclkList1();

	//-------------------------------------------------------------------
	//���ܺ���
	//-------------------------------------------------------------------
	void InitPMDispatcher();//��ʼ���ɷ����ڲ���Э��

	void gh_GameHallInit();//������ʼ��
	void gh_GameHallRun();//��������
	void gh_GameHallEnd();//��������

	//------------------
	//��½���
	//------------------
	void gh_LoginSuccess(_CNET_EVENT& ne);//��½�ɹ�
	void gh_NewClientLogin(_CNET_EVENT& ne);//����ҵ���

	//------------------
	//�������
	//------------------
	void gh_ChangeDataSuccess(_CNET_EVENT& ne);//�޸�������ϳɹ�
	void gh_ChangeDataFailed(_CNET_EVENT& ne);//�޸��������ʧ��
	void gh_PublicTalk(_CNET_EVENT& ne);//��������
	void gh_PrivateTalk(_CNET_EVENT& ne);//˽������
	void gh_PlayerOffLine(_CNET_EVENT& ne);//�������
	void gh_EnterRoomSuccess(_CNET_EVENT& ne);//���뷿��ɹ�
	void gh_EnterRoomFail(_CNET_EVENT& ne);//���뷿��ʧ��
	void gh_ReadSuccess(_CNET_EVENT& ne);//׼���ɹ�
	void gh_ExitRoomSuccess(_CNET_EVENT& ne);//�˳�����ɹ�
	void gh_ReadyCancelSuccess(_CNET_EVENT& ne);//ȡ��׼���ɹ�

	//------------------
	//��Ϸ���
	//------------------
	void gh_NewGame(_CNET_EVENT& ne);//�յ���ʼ����Ϸ��Ϣ
	void gh_UpdatePlayerData(_CNET_EVENT& ne);//�������״̬
	void gh_MakeChoice(_CNET_EVENT& ne);//ָ���������ѡ��
	void gh_TalkInGame(_CNET_EVENT& ne);//��ҽ�������
	void gh_GetNew(_CNET_EVENT& ne);//��һ�ȡ���µ���
	void gh_Win_21(_CNET_EVENT& ne);//��һ��21��ʤ��
	void gh_LoseOutRange(_CNET_EVENT& ne);//����򱬵�ʧ��
	void gh_LoseGiveUp(_CNET_EVENT& ne);//������������ʧ��
	void gh_LoseRunAway(_CNET_EVENT& ne);//��������ܱ���ʧ��
	void gh_WinBigger(_CNET_EVENT& ne);//������ձȵ�����ʤ
	void gh_Draw(_CNET_EVENT& ne);//������ձȵ���ƽ��
	void gh_GameEnd(_CNET_EVENT& ne);//�յ���Ϸ������Ϣ

public:
	afx_msg void OnBnClickedButton2();
public:
	afx_msg void OnBnClickedButton5();
public:
	CButton m_btRead;
};