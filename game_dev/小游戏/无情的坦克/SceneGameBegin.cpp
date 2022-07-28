#include "SceneGameBegin.h"
#include "GameEngine.h"
#include "ButtonUI.h"
#include "BmpButtonUI.h"
#include "SceneGameStage1.h"
#include "SceneGameStage2.h"
//������ʼ��
void CSceneGameBegin::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	SetEnterChange("��2");
	SetQuitChange("��2");
	LoadUI("��ʼ��Ϸ",new CBmpButtonUI(
		"pic\\��ʼ��Ϸ1.bmp",
		"pic\\��ʼ��Ϸ2.bmp",
		"pic\\��ʼ��Ϸ3.bmp",
		"pic\\��ʼ��Ϸ4.bmp",
		320,250,100,40,true,RGB(255,255,255)));
	LoadUI("��Ϸ˵��",new CBmpButtonUI(
		"pic\\��Ϸ˵��1.bmp",
		"pic\\��Ϸ˵��2.bmp",
		"pic\\��Ϸ˵��3.bmp",
		"pic\\��Ϸ˵��4.bmp",
		320,310,100,40,true,RGB(255,255,255)));
	LoadUI("�˳���Ϸ",new CBmpButtonUI(
		"pic\\�˳���Ϸ1.bmp",
		"pic\\�˳���Ϸ2.bmp",
		"pic\\�˳���Ϸ3.bmp",
		"pic\\�˳���Ϸ4.bmp",
		320,370,100,40,true,RGB(255,255,255)));
	LoadUI("����",new CBmpButtonUI(
		"pic\\����1.bmp",
		"pic\\����2.bmp",
		"pic\\����3.bmp",
		"pic\\����4.bmp",
		600,50,66,38,true,RGB(255,255,255)));
	LoadUI("ȷ��",new CButtonUI("ȷ��",230,400,100,30));
	GetUI("ȷ��")->SetView(false);
	GetUI("ȷ��")->SetAct(false);
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("��������","sound\\��������.mp3");
}
//������Ϣ
void CSceneGameBegin::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3(
		"pic\\��ʼ����.bmp",
		0, 0, 800, 600,
		0, 0,583,400);
	if(m_bJieShaoTu)
	{
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
			"pic\\����ͼ.bmp",150, 150, 162, 284,0, 0,162,320);
		CGameEngine::GetGE()->GetGO()->DrawBmp3(
			"pic\\ȷ��.bmp",260, 150, 50, 50,0, 0,66,38);

	}
}

void CSceneGameBegin::LogicInputRun()
{
}
//���볡��
void CSceneGameBegin::Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("��������");
	this->m_bJieShaoTu = false;
}
//�Ƴ�����
void CSceneGameBegin::Quit()
{
	
}
//UI��Ϣ
void CSceneGameBegin::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "��ʼ��Ϸ") == 0)
		{
			CGameEngine::GetGE()->GetScene("�ؿ�1")->SetRead(true);
			CGameEngine::GetGE()->GetScene("�ؿ�2")->SetRead(true);
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("e1");
			CGameEngine::GetGE()->SetCurScene("�ؿ�1");
		}
		else if (strcmp(id, "�˳���Ϸ") == 0)
			CGameEngine::GetGE()->ExitGame();
		else if (strcmp(id, "��Ϸ˵��") == 0)
		{
			this->m_bJieShaoTu = true;
			GetUI("ȷ��")->SetView(true);
			GetUI("ȷ��")->SetAct(true);
		}
		else if (strcmp(id, "ȷ��") == 0)
		{
			this->m_bJieShaoTu = false;
			GetUI("ȷ��")->SetView(false);
			GetUI("ȷ��")->SetAct(false);
		}
		else if (strcmp(id, "����") == 0)
		{
			if(CGameEngine::GetGE()->GetRF()->Open("save\\save1"))
			{
				int stage;
				int BianJieR;
				int BianJieD;
				int Score;
				int ItemsNum;
				int EnemyNum;
				int att;
				int dir;
				int life;
				POINT p;
				CGameEngine::GetGE()->GetRF()->ReadMemory(&stage,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&BianJieD,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&BianJieR,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&EnemyNum,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&Score,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&ItemsNum,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&att,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&dir,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&life,4);
				CGameEngine::GetGE()->GetRF()->ReadMemory(&p,sizeof(POINT));
				//��ȡ�ļ���������Ӧ�ؿ�
				if(stage == 1)
				{
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetBianjieD(BianJieD);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetBianjieR(BianJieR);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetEnemyNum(EnemyNum);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetScore(Score);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetItemsNum(ItemsNum);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetPlayerAtt(att);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetPlayerDir(dir);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetPlayerLife(life);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->GetLogicObject()->SetPlayerPoint(p);
					CGameEngine::GetGE()->GetScene("�ؿ�1")->SetRead(false);
					CGameEngine::GetGE()->SetCurScene("�ؿ�1");
				}
				if(stage == 2)
				{
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetBianjieD(BianJieD);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetBianjieR(BianJieR);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetEnemyNum(EnemyNum);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetScore(Score);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetItemsNum(ItemsNum);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetPlayerAtt(att);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetPlayerDir(dir);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetPlayerLife(life);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->GetLogicObject()->SetPlayerPoint(p);
					CGameEngine::GetGE()->GetScene("�ؿ�2")->SetRead(false);
					CGameEngine::GetGE()->SetCurScene("�ؿ�2");
				}
			}
			
		}
	}	
}
