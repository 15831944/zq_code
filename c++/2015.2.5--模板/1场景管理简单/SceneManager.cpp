#include "SceneManager.h"
#include "Scene.h"

CSceneManager::CSceneManager()
:
m_pScene(new CScene*[8]),
m_iSceneNum(0),
m_iSceneCur(-1),
m_bPlay(true)
{}
CSceneManager::~CSceneManager()
{
	if(m_pScene)
		delete []m_pScene;
}
//��ӳ���-��ӳ��������ָ��
bool CSceneManager::AddScene(CScene* pScene)
{
	if(m_iSceneNum == 8)
		return false;
	m_pScene[m_iSceneNum++] = pScene;
	return true;
}
//���õ�ǰ����
bool CSceneManager::SetCurScene(int CurScene)
{
	if(CurScene < 0||CurScene >= m_iSceneNum)
		return false;
	m_iSceneCur = CurScene;
	return true;
}
//�õ���ǰ����
CScene* CSceneManager::GetCurScene(int Scene)
{
	if(Scene < 0||Scene >= m_iSceneNum)
		return 0;
	return m_pScene[Scene];
}
//��Ϸѭ���ı�־
bool CSceneManager::Play()
{
	return m_bPlay;
}
//�˳���Ϸ
void CSceneManager::Exit()
{
	m_bPlay = false;
}
//��Ϸ����
void CSceneManager::GameRun()
{
	while(m_bPlay)
	{
		m_pScene[m_iSceneCur]->Run();
	}
}
