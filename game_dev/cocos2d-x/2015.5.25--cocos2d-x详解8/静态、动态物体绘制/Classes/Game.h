#ifndef __GAME_H__
#define __GAME_H__

#include "GameLayer.h"
#include <list>

#define _MAP_W 64 //��ͼ���߼���
#define _MAP_H 64 //��ͼ���߼���
#define _MAP_S (_MAP_W * _MAP_H) //��ͼ���߼���С

//��̬�������
class DynamicElementManager
{
public:
	int m_MapW, m_MapH; //��ͼ�����ؿ����ظ�
	int m_AreaW, m_AreaH; //��������ؿ����ظ�
	int m_AreaXNum, m_AreaYNum, m_AreaNum; //�����X����������Y��������������
	std::list<CCRect> m_Elements; //��������
	std::list<CCRect*>* m_AreaList; //�����

	//���ݾ��εõ��þ��ο�Խ������
	int GetArea(CCRect* r, int* a);

	//����
	DynamicElementManager(
		int MapW, int MapH,
		int AreaXNum, int AreaYNum);

	//����
	~DynamicElementManager();

	//��������
	CCRect* CreateDE(const CCRect& r);

	//ɾ������
	bool DeleteDE(CCRect* e);

	//�ƶ�����
	bool MoveDE(CCRect* e, int mx, int my);

	//�õ���������
	void GetRenderDE(
		const CCRect& view,
		std::list<CCRect*>* m_RenderDEList);
};

class CGame : public CGameLayer
{
	CCTexture2D* t0;
	CCTexture2D* t1;
	char map[_MAP_S];
	int x, y; //Ӣ���ڴ��ͼ���������

public:

	CGame();

	//virtual void Enter();
	//virtual void InputDown(CCPoint* p);
	//virtual void InputMove(CCPoint* p, int n);
	virtual void InputUp(CCPoint* p);
	virtual void Output();
	virtual void Logic(float dt);
	//virtual void Exit();
	void OnUIMessage(int id, int msg);
};

#endif