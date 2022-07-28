//����ר�����������ҹ���
//���ϵı�����һ���ź����˳���
//�����в��������ظ�������

#ifndef _SET_H_
#define _SET_H_

#define SDATA int

typedef struct _SET
{
	bool (*smaller)(SDATA,SDATA);
	int size;
	int length;
	SDATA* data;
}* SET;

//����(����)
SET createSET(bool (*smaller)(SDATA,SDATA),int size = 8);
//����(����)
void destorySET(SET set);
//����(���ϣ�����)
bool insertSET(SET set,SDATA data);
//ɾ��(���ϣ�����)
bool eraseSET(SET set,SDATA data);
//����(���ϣ�����)
SDATA* findSET(SET set,SDATA data);

#endif