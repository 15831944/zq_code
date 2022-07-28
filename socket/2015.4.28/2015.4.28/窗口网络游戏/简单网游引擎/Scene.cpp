#include "Scene.h"
#include "UI.h"

CScene::CScene():m_KeyUI(0){}
CScene::~CScene(){}
void CScene::Init(){}
void CScene::Enter(){}
void CScene::OutputRun(){}
void CScene::InputRun(){}
void CScene::LogicRun(){}
void CScene::Quit(){}
void CScene::End(){}
void CScene::OnUIMessage(int message, const char* id){}
void CScene::OnNetEvent(_TC_NET_EVENT* ptne){}

bool CScene::LoadUI(CUI* pUI, const char* id)
{
	std::string str = id;
	if (m_UIs.Find(str))
		return false;

	//�õ�ID�źͳ���
	pUI->m_ID = id;
	pUI->m_Scene = this;
	
	//װ��ӳ��
	return m_UIs.Insert(str, pUI);
}

bool CScene::SetKeyUI(const char* id)
{
	//���������ַ���Ϊ���������ǰ�����еļ��̽���ؼ�
	if (id == 0)
	{
		m_KeyUI = 0;
		return true;
	}
	else
	{
		std::string str = id;
		CMap<std::string, CUI*>::PAIR* p = m_UIs.Find(str);
		if (p)
		{
			m_KeyUI = p->data;
			return true;
		}
		else
			return false;
	}
}

CUI* CScene::GetKeyUI()
{
	return m_KeyUI;
}

CUI* CScene::GetUI(const char* id)
{
	std::string str = id;
	CMap<std::string, CUI*>::PAIR* p = m_UIs.Find(str);
	return p ? p->data : 0;
}
	