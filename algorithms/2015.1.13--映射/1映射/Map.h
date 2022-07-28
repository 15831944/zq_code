//ӳ��ר�����������ҹ���,�Ǹ���KEYֵȥ����DATA
//ӳ��ı�����һ������KEYֵ�ź����˳���
//ӳ���в��������ظ���KEYֵ���������ظ�������

#ifndef _MAP_H_
#define _MAP_H_

#define MKEY int
#define MDATA char*

typedef struct _MAP
{
	bool (*smaller)(MKEY,MKEY);
	int size;
	int length;
	MKEY* key;
	MDATA* data;
}* MAP;

//����(����)
MAP createMAP(bool (*smaller)(MKEY,MKEY),int size = 8);
//����(ӳ��)
void destoryMAP(MAP map);
//����(ӳ�䣬��ֵ������)
bool insertMAP(MAP map,MKEY key,MDATA data);
//ɾ��(ӳ�䣬��ֵ)
bool eraseMAP(MAP map,MKEY key);
//����(ӳ�䣬��ֵ)
MDATA* findMAP(MAP map,MKEY key);

#endif