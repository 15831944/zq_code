#ifndef _PROTOCOL_INDEX_H_
#define _PROTOCOL_INDEX_H_
#include "DataDefine.h"

class CGameHallDlg;

class CProtocolIndex
{
protected:
	CGameHallDlg* m_pCGameHallDlg;
public:
	CProtocolIndex(CGameHallDlg* p);
	virtual void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//��½���
//--------------------------------------------------------------------------------------
//�ͻ��˵�¼�ɹ�Э��
class CPI_LoginSuccess : public CProtocolIndex
{
public:
	CPI_LoginSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ�������ҵ�¼Э��
class CPI_NewClientLogin : public CProtocolIndex
{
public:
	CPI_NewClientLogin(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//�������
//--------------------------------------------------------------------------------------
//�ͻ����޸����ϳɹ�Э��
class CPI_DataChangeSuccess : public CProtocolIndex
{
public:
	CPI_DataChangeSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ����޸�����ʧ��Э��
class CPI_DataChangeFailed : public CProtocolIndex
{
public:
	CPI_DataChangeFailed(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ��˹�������Э��
class CPI_PublicTalk : public CProtocolIndex
{
public:
	CPI_PublicTalk(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ���˽������Э��
class CPI_PrivateTalk : public CProtocolIndex
{
public:
	CPI_PrivateTalk(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ����������Э��
class CPI_PlayerOffLine : public CProtocolIndex
{
public:
	CPI_PlayerOffLine(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ��˽��뷿��ɹ�
class CPI_EnterRoomSuccess : public CProtocolIndex
{
public:
	CPI_EnterRoomSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ��˽��뷿��ʧ��
class CPI_EnterRoomFail : public CProtocolIndex
{
public:
	CPI_EnterRoomFail(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ���׼���ɹ�
class CPI_ReadSuccess : public CProtocolIndex
{
public:
	CPI_ReadSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ����˳�����ɹ�
class CPI_ExitRoomSuccess : public CProtocolIndex
{
public:
	CPI_ExitRoomSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�ͻ���ȡ��׼���ɹ�
class CPI_ReadyCancelSuccess : public CProtocolIndex
{
public:
	CPI_ReadyCancelSuccess(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//--------------------------------------------------------------------------------------
//��Ϸ���
//--------------------------------------------------------------------------------------
//��ʼ����Ϸ
class CPI_NewGame : public CProtocolIndex
{
public:
	CPI_NewGame(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//�����������
class CPI_UpdatePlayerData : public CProtocolIndex
{
public:
	CPI_UpdatePlayerData(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//ָ���������ѡ��
class CPI_MakeChoice : public CProtocolIndex
{
public:
	CPI_MakeChoice(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//ָ����ҽ�������
class CPI_TalkInGame : public CProtocolIndex
{
public:
	CPI_TalkInGame(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//��һ�ȡ���µ���
class CPI_GetNew : public CProtocolIndex
{
public:
	CPI_GetNew(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//��һ��21��ʤ��
class CPI_Win_21 : public CProtocolIndex
{
public:
	CPI_Win_21(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//����򱬵�ʧ��
class CPI_LoseOutRange : public CProtocolIndex
{
public:
	CPI_LoseOutRange(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//������������ʧ��
class CPI_LoseGiveUp : public CProtocolIndex
{
public:
	CPI_LoseGiveUp(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//��������ܱ���ʧ��
class CPI_LoseRunAway : public CProtocolIndex
{
public:
	CPI_LoseRunAway(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//������ձȵ�����ʤ
class CPI_WinBigger : public CProtocolIndex
{
public:
	CPI_WinBigger(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
//������ձȵ���ƽ��
class CPI_Draw : public CProtocolIndex
{
public:
	CPI_Draw(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};

//��Ϸ������Ϣ
class CPI_GameEnd : public CProtocolIndex
{
public:
	CPI_GameEnd(CGameHallDlg* p);
	void ProtocolFun(_CNET_EVENT& ne);
};
#endif