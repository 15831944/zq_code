#include "1.h"
#include "GameEngine.h"

void C1::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadDirectory("pic");
	CGameEngine::GetGE()->GetGO()->LoadFont(
		"��ʼ��������",
		30, 20, 400, false, false, false, "����");

	SetEnterChange("��2");
	SetQuitChange("��2");
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
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_RETURN) == _KS_UC)
		CGameEngine::GetGE()->SetCurScene("��Ϸ����");

	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_ESC) == _KS_UC)
		CGameEngine::GetGE()->ExitGame();
}

