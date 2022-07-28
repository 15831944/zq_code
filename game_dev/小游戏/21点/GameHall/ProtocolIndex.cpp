#include "Resource.h"
#include "GameHallDlg.h"
#include "ProtocolIndex.h"

CProtocolIndex::CProtocolIndex(CGameHallDlg* p)
:
m_pCGameHallDlg(p)
{}

void CProtocolIndex::ProtocolFun(_CNET_EVENT& ne)
{}

//--------------------------------------------------------------------------------------
//��½���
//--------------------------------------------------------------------------------------

//�ͻ��˵�¼�ɹ�Э��
CPI_LoginSuccess::CPI_LoginSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoginSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoginSuccess(ne);
}

//�ͻ�������ҵ�¼Э��

CPI_NewClientLogin::CPI_NewClientLogin(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_NewClientLogin::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_NewClientLogin(ne);
}

//--------------------------------------------------------------------------------------
//�������
//--------------------------------------------------------------------------------------

//�ͻ����޸����ϳɹ�Э��
CPI_DataChangeSuccess::CPI_DataChangeSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_DataChangeSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ChangeDataSuccess(ne);
}

//�ͻ����޸�����ʧ��Э��
CPI_DataChangeFailed::CPI_DataChangeFailed(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_DataChangeFailed::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ChangeDataFailed(ne);
}

//�ͻ��˹�������Э��
CPI_PublicTalk::CPI_PublicTalk(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PublicTalk::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PublicTalk(ne);
}

//�ͻ���˽������Э��
CPI_PrivateTalk::CPI_PrivateTalk(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PrivateTalk::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PrivateTalk(ne);
}

//�ͻ����������Э��
CPI_PlayerOffLine::CPI_PlayerOffLine(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_PlayerOffLine::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_PlayerOffLine(ne);
}

//�ͻ��˽��뷿��ɹ�
CPI_EnterRoomSuccess::CPI_EnterRoomSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_EnterRoomSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_EnterRoomSuccess(ne);
}

//�ͻ����������Э��
CPI_EnterRoomFail::CPI_EnterRoomFail(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_EnterRoomFail::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_EnterRoomFail(ne);
}

//�ͻ���׼���ɹ�
CPI_ReadSuccess::CPI_ReadSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}
void CPI_ReadSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ReadSuccess(ne);
}

//�ͻ����˳�����ɹ�
CPI_ExitRoomSuccess::CPI_ExitRoomSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_ExitRoomSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ExitRoomSuccess(ne);
}

//�ͻ���ȡ��׼���ɹ�
CPI_ReadyCancelSuccess::CPI_ReadyCancelSuccess(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_ReadyCancelSuccess::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_ReadyCancelSuccess(ne);
}

//--------------------------------------------------------------------------------------
//��Ϸ���
//--------------------------------------------------------------------------------------
//��ʼ����Ϸ
CPI_NewGame::CPI_NewGame(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_NewGame::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_NewGame(ne);
}

//�������ս��
CPI_UpdatePlayerData::CPI_UpdatePlayerData(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_UpdatePlayerData::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_UpdatePlayerData(ne);
}

//ָ���������ѡ��
CPI_MakeChoice::CPI_MakeChoice(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_MakeChoice::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_MakeChoice(ne);
}

//ָ����ҽ�������
CPI_TalkInGame::CPI_TalkInGame(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_TalkInGame::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_TalkInGame(ne);
}

//��һ�ȡ���µ���
CPI_GetNew::CPI_GetNew(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_GetNew::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_GetNew(ne);
}

//��һ��21��ʤ��
CPI_Win_21::CPI_Win_21(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_Win_21::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_Win_21(ne);
}

//����򱬵�ʧ��
CPI_LoseOutRange::CPI_LoseOutRange(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseOutRange::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseOutRange(ne);
}

//������������ʧ��
CPI_LoseGiveUp::CPI_LoseGiveUp(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseGiveUp::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseGiveUp(ne);
}

//��������ܱ���ʧ��
CPI_LoseRunAway::CPI_LoseRunAway(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_LoseRunAway::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_LoseRunAway(ne);
}

//������ձȵ�����ʤ
CPI_WinBigger::CPI_WinBigger(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_WinBigger::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_WinBigger(ne);
}

//������ձȵ���ƽ��
CPI_Draw::CPI_Draw(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_Draw::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_Draw(ne);
}

//��Ϸ������Ϣ
CPI_GameEnd::CPI_GameEnd(CGameHallDlg* p)
:
CProtocolIndex(p)
{}

void CPI_GameEnd::ProtocolFun(_CNET_EVENT &ne)
{
	m_pCGameHallDlg->gh_GameEnd(ne);
}
