#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <vector>
#include <windows.h>
//��Ϸ�߼��࣬��Ϸͨ�����ø������ʵ�ֶ�������ϷԪ�ص�
//�߼�����

class CPlane;
class CBullet;

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

	//����Ӣ�۹���
	void SetHeroAttack(POINT point);

	//��ȡӢ�۷ɻ���λ��
	POINT GetHeroPoint();

	//��ײ���
	void PengZhuangJianCe();

	//����.д��������в�����
	void Paint(HWND hWnd);

	//�����ӵл�
	void AddEmenyPlane();

	void Brom();
};

#endif