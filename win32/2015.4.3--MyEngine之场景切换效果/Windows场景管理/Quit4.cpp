#include "Quit4.h"
#include "GameEngine.h"

CQuit4::CQuit4()
:
CSceneChange(36)
{
	w = CGameEngine::GetGE()->GetW() / 6;
	h = CGameEngine::GetGE()->GetH() / 6;
}
void CQuit4::Render(int CurFrame)
{
	if(1 == CurFrame)
	{
		int temp[36];
		for(int i = 0; i < 36; ++i)
			temp[i] = i;
		//����
		for(int i = 35; i > 0; --i)
		{
			int j = CGameEngine::GetRandomNum(0,i);
			int k = temp[j];
			temp[j] = temp[i];
			temp[i] = k;
		}

		for(int i = 0 ; i < 36; ++i)
			index[i] = temp[i];
	}

	for(int i = 0; i < CurFrame; ++i)
	{
		int x = index[i] % 6;
		int y = index[i] / 6;
		CGameEngine::GetGE()->GetGO()->DrawRectangle2(
			x * w,y * h,(x + 1) * w, (y + 1) * h,
			RGB(0,0,0),RGB(0,0,0));
	}
}