#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;

//����������
class CSceneManager
{
	CScene** m_pScene;//�洢����ָ��
	int m_iSceneNum;//��������
	int m_iSceneCur;//��ǰ����
	bool m_bPlay;//��Ϸѭ����־
public:
	CSceneManager();
	~CSceneManager();
	//��ӳ���
	bool AddScene(CScene* pScene);
	//���õ�ǰ����
	bool SetCurScene(int CurScene);
	//�õ���ǰ����
	CScene* GetCurScene(int Scene);
	//��Ϸѭ���ı�־
	bool Play();
	//�˳���Ϸ
	void Exit();
	//��Ϸ����
	void GameRun();
};

#endif