#ifndef _ACT_GAME_H_
#define _ACT_GAME_H_

#include <list>

//���νṹ��
struct _RECTANGLE
{
	int x1, y1; //���Ͻ�x��y����
	int x2, y2; //���½�x��y����
};

//������ײ
bool RectCollide(const _RECTANGLE* r1,
				 const _RECTANGLE* r2,
				 _RECTANGLE* r3);

//����ṹ��
struct _OBJECT
{
	_RECTANGLE r;
	int csx, csy;
	int ksx, ksy;
	int asx, asy;
};

class CActGame
{
	int m_MapLW, m_MapLH; //��ͼ�߼�����
	int m_MapPW, m_MapPH; //��ͼ���ؿ���
	int m_GridW, m_GridH; //���ӵ����ؿ���
	char* m_Map; //����С�ڵ���0�����ݶ����ϰ�����

	std::list<_OBJECT> m_ObjList; //�����

public:

	//������Լ��Ͽ��������ͬ�ำֵ��

	//����
	CActGame(
		int MapLW, int MapLH,
		int GridW, int GridH);

	//����
	~CActGame();

	//���õ�ͼ
	bool SetMap(int x, int y, char d);

	//�õ���ͼ
	char* GetMap(int x, int y);

	//��������
	_OBJECT* CreateObject(
		_RECTANGLE* r, //�������
		int csx = 0, int csy = 0, //˲ʱ�ٶȣ�current speed��
		int ksx = 0, int ksy = 0, //�����ٶȣ�keep speed��
		int asx = 0, int asy = 0); //���ٶȣ�accelerate speed��

	//�ƶ�����
	bool MoveObject(
		_OBJECT* obj,
		int st, //�ٶ����ͣ�012�ֱ����˲ʱ�ٶȡ������ٶȡ����ٶ�
		int sx, int sy); //�ٶ�����

	//ɾ������
	bool EraseObject(_OBJECT* obj);

	//����
	void Run();
};

#endif