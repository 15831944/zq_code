#include "2.h"
#include "GameEngine.h"	

void C2::Init()
{
	CGameEngine::GetGE()->GetGO()->LoadFont("��Ϸ����",
		40,40,400,false,false,false,"���Ĳ���");
	x = y = 0;

	SetEnterChange("��1");
	SetQuitChange("��1");
}
void C2::OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp2("pic\\δ����.bmp",0,0,640,480,0,0);
	CGameEngine::GetGE()->GetGO()->DrawBmp1("pic\\1.bmp",x,y,40,70,0,0);
	CGameEngine::GetGE()->GetGO()->DrawString1("��Ϸ����",0,0,"��ESC����",RGB(255,255,0));

	//if(time < 64)
	//{
	//	unsigned char x1 = CGameEngine::GetGE()->GetGO()->GetDark();
	//	CGameEngine::GetGE()->GetGO()->SetDark(x1 + 4);
	//	time += 1;
	//}
	
}

void C2::LogicInputRun()
{
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_W) == _KS_DH)
		y -= 5;
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_S) == _KS_DH)
		y += 5;
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_A) == _KS_DH)
		x -= 5;
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_D) == _KS_DH)
		x += 5;
	if(CGameEngine::GetGE()->GetGI()->Get(_GI_K_ESC) == _KS_UC)
		CGameEngine::GetGE()->SetCurScene("��ʼ����");
}

void C2::Enter()
{
	time = 0;
}
