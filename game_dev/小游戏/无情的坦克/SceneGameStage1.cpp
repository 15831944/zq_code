#include "SceneGameStage1.h"
#include "GameEngine.h"
#include "BmpButtonUI.h"
#include "ButtonUI.h"
#include "Player.h"
#include "GameLogic.h"

CGameLogic* CSceneGameStage1:: GetLogicObject()
{
	return &stage1;
}
//������ʼ��
void CSceneGameStage1::Init()
{
	SetEnterChange("��2");
	SetQuitChange("��2");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("������","sound\\sound194.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�������","sound\\sound195.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("��ը","sound\\sound220.mp3");
	CGameEngine::GetGE()->GetAM()->PushOnceAudio("�������","sound\\����.mp3");
	LoadUI("�浵",new CBmpButtonUI(
		"pic\\�浵1.bmp",
		"pic\\�浵2.bmp",
		"pic\\�浵3.bmp",
		"pic\\�浵4.bmp",
		700,30,66,38,true,RGB(255,255,255)));
	this->m_bIsRead = true;
}
//���볡��
void CSceneGameStage1::Enter()
{
	this->m_bBoFang = false;
	this->m_bGameEnd = true;
	if(this->m_bIsRead)
	{
		this->m_iStage = 1;
		stage1.GameInit();
	}
	stage1.SetMapStage1();
	stage1.SetStage(1);
	this->m_iTime = 0;
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("��������");

}
//���Ƶ�ͼԪ�صĺ���
void CSceneGameStage1::OutputRun()
{
	//������ϷԪ��
	stage1.Paint();
	//�Ƿ������Ϸ
	if(!m_bGameEnd)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\��Ϸ����.bmp",
		100, 100, 486, 227,
		0, 0,486,227);
		if(!m_bBoFang)
		{
			CGameEngine::GetGE()->GetAM()->StopLoopAudio("��������");
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("�������");
			m_bBoFang = true;
		}
	}
	if(m_iTime < 15)
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\��һ��.bmp",200, 100, 294, 106,0, 0,294,106);
	//�������ƣ�i������Ϸ��t�˳���Ϸ
	
}
//��ǰ�����߼�����ĺ���
void CSceneGameStage1::LogicInputRun()
{
	//���ơ���һ�ء�����ͼƬ
	if(m_iTime<15)
	{
		m_iTime ++;
		if(m_iTime == 15)
			m_iTime =15;
	}
	//�������С��0����Ϸ����
	if(stage1.GetPlayerLife() <=0)
	{
		m_bGameEnd = false;
		this->m_bIsRead = true;
	}
	if(m_bGameEnd)
	{
		stage1.PlayerMove();
		stage1.GameRun();
	}
	else
	{
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
			CGameEngine::GetGE()->ExitGame();
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_I) == _KS_DC)
			CGameEngine::GetGE()->SetCurScene("��Ϸ��ʼ");
	}
	//������Ŀ�ﵽ�涨��Ŀ������ڶ���
	if(stage1.GetEnemyNum()<=0)
	{
		CGameEngine::GetGE()->SetCurScene("�ؿ�2");
	}
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_T) == _KS_DC)
		CGameEngine::GetGE()->ExitGame();
}

//�˳�����
void CSceneGameStage1::Quit()
{

}
void CSceneGameStage1::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "�浵") == 0)
		{
			stage1.WriteGame();
		}
	}
}
void CSceneGameStage1:: SetRead(bool set)
{
	this->m_bIsRead = set;
}
bool CSceneGameStage1::GetSetRead()
{
	return this->m_bIsRead;
}