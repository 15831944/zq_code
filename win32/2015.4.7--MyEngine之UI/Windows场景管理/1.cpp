#include "1.h"
#include "GameEngine.h"
#include "ButtonUI.h"

void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"��ʼ��������",
		30, 20, 400, false, false, false, "����");

	SetEnterChange("��4");
	SetQuitChange("��4");

	LoadUI("��ʼ��ť", new CButtonUI("Start", 0, 0, 100, 30));
	LoadUI("������ť", new CButtonUI("Exit", 0, 200, 100, 30));
}

void C1::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp2(
		"pic\\Bliss.bmp",
		0, 0, 640, 480,
		0, 0);

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"��ʼ��������", 0, 0, "���س�������Ϸ", RGB(255, 0, 0));

	CGameEngine::GetGE()->GetGO()->DrawString1(
		"��ʼ��������", 0, 50, "��ESC�˳���Ϸ", RGB(255, 0, 255));
}

void C1::LogicInputRun()
{
}

void C1::OnUIMsg(const char* id, int UIMSG)
{
	if (UIMSG == _BUTTON_CLICK)
	{
		if (strcmp(id, "��ʼ��ť") == 0)
			CGameEngine::GetGE()->SetCurScene("��Ϸ����");
		else if (strcmp(id, "������ť") == 0)
			CGameEngine::GetGE()->ExitGame();
	}
}
