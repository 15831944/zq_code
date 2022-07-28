#include "GameLogo.h"
#include "GameEngine.h"
//������ʼ��
void CGameLogo :: Init()
{
	this->m_iTime = 0;
	SetEnterChange("��2");
	SetQuitChange("��2");
	CGameEngine::GetGE()->GetAM()->PushLoopAudio("��ĭ","sound\\��ĭ.mp3");
}
//���
void CGameLogo :: OutputRun()
{
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\����logo.bmp",
		0, 0, 800, 600,0, 0,641,508);
}
//�߼�����
void CGameLogo :: LogicInputRun()
{
	if(m_iTime == 20)
		CGameEngine::GetGE()->SetCurScene("��Ϸ��ʼ");
	m_iTime++;
}
//���볡��
void CGameLogo :: Enter()
{
	CGameEngine::GetGE()->GetAM()->PlayLoopAudio("��ĭ");
}