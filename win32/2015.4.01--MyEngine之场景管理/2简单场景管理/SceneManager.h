#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;

class CSceneManager
{
	static CScene* m_Scene[8];//��������ָ������
	static int m_SceneNum;//��ǰ�Ѿ��еĳ�������
	static int m_CurScene;//��ǰ�������
	static bool m_Play;//�Ƿ�ʼ��Ϸ
public:
	//���س���
	static bool LoadScene(CScene* pScene);

	//���õ�ǰ����
	static bool SetCurScene(int index);

	//�˳���Ϸ
	static void Exit();

	//����
	void Run();
};

#endif