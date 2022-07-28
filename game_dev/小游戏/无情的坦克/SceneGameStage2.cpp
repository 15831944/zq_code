#include "SceneGameStage2.h"
#include "GameEngine.h"
#include "BmpButtonUI.h"
#include "ButtonUI.h"
#include "Player.h"
#include "GameLogic.h"
//CGameLogic stage2;

CGameLogic* CSceneGameStage2:: GetLogicObject()
{
	return &stage2;
}
//����2�ĳ�ʼ��
void CSceneGameStage2::Init()
{
	SetEnterChange("��2");
	SetQuitChange("��2");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("������","sound\\sound194.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��Ϸʤ��","sound\\��Ϸʤ��.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�������","sound\\sound195.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��ը","sound\\sound220.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�������","sound\\����.mp3");
	LoadUI("�浵",new CBmpButtonUI(
		"pic\\�浵1.bmp",
		"pic\\�浵2.bmp",
		"pic\\�浵3.bmp",
		"pic\\�浵4.bmp",
		700,30,66,38,true,RGB(255,255,255)));
	m_bIsRead = true;
}
//���볡��
void CSceneGameStage2::Enter()
{
	//�Ƿ���ͨ����ȡ�ļ������
	if(m_bIsRead)
	{
		this->m_iStage = 2;
		stage2.GameInit();
	}
	this->m_bGameVictor = false;
	this->m_bGameEnd = true;
	m_bBoFangshibai = false;
	m_bBoFangWin = false;
	this->m_iTime = 0;
	stage2.SetStage(2);
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("��������");
}
//���Ƶ�ͼԪ�صĺ���
void CSceneGameStage2::OutputRun()
{
	stage2.Paint();
	if(!m_bGameEnd)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\��Ϸ����.bmp",
		100, 100, 486, 227,
		0, 0,486,227);
		if(!m_bBoFangshibai)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("��������");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("�������");
			m_bBoFangshibai = true;
		}
	}
	if(m_bGameVictor)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\��Ϸʤ��.bmp",
		100, 100, 486, 227,
		0, 0,403,232);
		if(!m_bBoFangWin)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("��������");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("��Ϸʤ��");
			m_bBoFangWin = true;
		}
	}
	if(m_iTime < 15)
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\�ڶ���.bmp",200, 100, 294, 106,0, 0,294,106);
}
//��ǰ�����߼�����ĺ���
void CSceneGameStage2::LogicInputRun()
{
	if(m_iTime<15)
	{
		m_iTime ++;
		if(m_iTime == 15)
			m_iTime =15;
	}
	//�ж������������С��0��������Ϸ
	if(stage2.GetPlayerLife() <=0)
		m_bGameEnd = false;
	//��Ϸ�Ƿ�ʤ��
	if(stage2.GetEnemyNum()<=0)
		m_bGameVictor = true ;
	if(m_bGameEnd && !m_bGameVictor)
	{
		stage2.PlayerMove();
		stage2.GameRun();
	}
	else
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("��Ϸ��ʼ");
	}
	if(m_bGameVictor)
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("��Ϸ��ʼ");
	}
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
		CGameEngine::GetGE()->ExitGame();
}
//UI��Ϣ
void CSceneGameStage2::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "�浵") == 0)
		{
			stage2.WriteGame();
		}
	}
}
//�����Ƿ��Ƕ���������Ϸ
void CSceneGameStage2:: SetRead(bool set)
{
	this->m_bIsRead = set;
}
//�˳�����
void CSceneGameStage2::Quit()
{
	CGameEngine::GetGE()->GetAM()->StopLoopAudio("�˳�����");
}