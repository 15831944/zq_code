#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <vector>

//��Ϸ�߼��࣬��Ϸͨ�����ø������ʵ�ֶ�������ϷԪ�ص�
//�߼�����
class CGameLogic
{
	int m_iScore;//�÷� 
	std::vector<CPlane*> m_vEmenyPlane;//�ɻ���-���˵�
	CPlane* m_pHeroPlane;//�ɻ���Ӣ��
	std::vector<CBullet*> m_vEmenyBullet;
	std::vector<CBullet*> m_vHeroBullet;
	int m_iBianJieRight;//�ұ߽�
	int m_iBianJieBottom;//�±߽�
public:
	CGameLogic();
	~CGameLogic();

	//��ʼ�����������߽�
	void Init(int score,int bianjr,int bianjb);

	//����
	void Run();

	//����Ӣ��λ��
	void SetHeroPoint(POINT point);

	
};

#endif