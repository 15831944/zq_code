#include "SceneManager.h"
#include "Scene.h"
#include <windows.h>

CScene* CSceneManager::m_Scene[8];//��������ָ������
int CSceneManager::m_SceneNum = 0;//��������
int CSceneManager::m_CurScene = -1;//��ǰ�������
bool CSceneManager::m_Play = true;//�Ƿ�ʼ��Ϸ
//���س���
bool CSceneManager::LoadScene(CScene* pScene)
{
	if(m_SceneNum == 8)
		return false;
	m_Scene[m_SceneNum ++] = pScene;
	return true;
}
//���õ�ǰ����
bool CSceneManager::SetCurScene(int index)
{
	if(index < 0 || index >= m_SceneNum)
		return false;
	m_CurScene = index;
	return true;
}

//�˳���Ϸ
void CSceneManager::Exit()
{
	m_Play = false;
}

//����
void CSceneManager::Run()
{
	while(m_Play)
	{
		m_Scene[m_CurScene]->Run();
		Sleep(33);
	}
}