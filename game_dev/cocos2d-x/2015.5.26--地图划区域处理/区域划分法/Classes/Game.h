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

	DynamicElementManager dem;
	struct _MONSTER
	{
		CCRect* id; //�����ַ
		int dir; //�ƶ�����0123������������
		int move; //�ƶ�����
	};
	std::list<_MONSTER> m_Monster; //�����

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

//struct _RECTANGLE
//{
//	int x1, y1, x2, y2;
//};
//
//bool RectCollide(const _RECTANGLE* r1,
//				 const _RECTANGLE* r2,
//				 _RECTANGLE* r3)
//{
//	if (r1->x1 > r2->x2 ||
//		r2->x1 > r1->x2 ||
//		r1->y1 > r2->y2 ||
//		r2->y1 > r1->y2)
//		return false;
//	else
//	{
//		*r3 = *r1;
//		if (r2->x1 > r1->x1)
//			r3->x1 = r2->x1;
//		if (r2->x2 < r1->x2)
//			r3->x2 = r2->x2;
//		if (r2->y1 > r1->y1)
//			r3->y1 = r2->y1;
//		if (r2->y2 < r1->y2)
//			r3->y2 = r2->y2;
//		return true;
//	}
//}

//�ڴ�����Ϸ�е���ײ���ʱ��Ҳ����ʹ�����������򻮷ַ���һ��
//��˵��ײ��������Ӧ�ñȿɼ��Լ�黹ҪС��һ�������ƶ�֮��
//�ǿ��Ը���������жϳ��������ĸ��������������ĸ�������Ȼ
//�����ʱ���ֻ��Ҫ�������ڵ�����������������������ײ��
//�⼴�ɣ���������������������ǲ����ܺ�������巢����ײ��

#endif