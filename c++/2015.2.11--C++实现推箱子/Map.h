//--------------------------
//CMap�ࣺ
//��¼��ͼ�����飬��Ҫ�����ͼ�ĳ�ʼ��
//(�ȵ�ͼ�ؿ����л�)����ϷԪ�ص�λ�÷����仯��ʱ��
//�ı�ö�Ӧλ�õ�����Ԫ��ֵ������ͼ��ʵʱ��״������Ⱦ
//����
//--------------------------
#ifndef _MAP_H_
#define _MAP_H_

class CGameRole;

class CMap
{
	int m_iWidth;//��ͼ��
	int m_iHeight;//��ͼ��
	
	int m_iGuanQiaZongShu;//�ؿ�����
	int m_iDangQianGuanQia;//��ǰ�ؿ�

	int m_iMapSLength;//��ͼ���ܴ�С
	int m_iMapELength;//ÿ���ؿ��ĵ�ͼ��С
	char* m_pMapSum;//�ܵ�ͼ�Ķ�����
	char* m_pMap;//ÿ���ؿ��ĵ�ͼ����
	CGameRole* m_pRole;//��ϷԪ������
public:

	~CMap();

	void Release();

	//�ڶ�ȡ��ͼ��ʱ����ã��Դ����洢��ͼ���ڴ�ռ�
	void InitMap(int gqzs,int zditudaxiao,char* pmap,int w,int h);

	//�ڶ�ȡ�ؿ���ͼ��ʱ��ʹ��-��ȡ�浵����
	void LoadMap(int dqgq,char* pdqmap);

	//��ȡ�ܵ�ͼ����ĵ�ַ
	char* GetMapSum();

	//��ȡ��ǰ�ؿ��ĵ�ͼ����
	char* GetMap();

	//���õ�ǰ�ؿ��ĵ�ͼ
	void SetGuanQiaMap();

	//���õ�ǰ�ؿ�
	void SetGuanQia(int guanqia);

	//��ȡ��ǰ�ؿ�
	int GetGuanQia();

	//������Ϸ��ͼԪ��-�߼��е���
	bool SetMapData(int x,int y,char c);
	
	int GetWidth();

	int GetHeight();

	int GetMapDaXiao();
};

#endif