#ifndef _SQLIST_H_
#define _SQLIST_H_

#define SLDATA int

typedef struct _SQ_LIST
{
	int size;//����
	int length;//����
	SLDATA* data;//����
}* SQLIST;

//����(����)
SQLIST createSQLIST(int size = 8);
//����(˳���)
void destroySQLIST(SQLIST sqlist);
//����(˳������ݣ�λ��)
bool insertSQLIST(SQLIST sqlist,SLDATA data,int pos);
//����(˳�������)
void pushSQLIST(SQLIST sqlist,SLDATA data);
//ɾ��(˳���λ��)
bool eraseSQLIST(SQLIST sqlist,int pos);
//���(˳���)
void clearSQLIST(SQLIST sqlist);
//����(˳���)
int lengthSQLIST(SQLIST sqlist);
//��ȡ(˳���λ��)
SLDATA* getSQLIST(SQLIST sqlist,int pos);
//����(˳������ݣ���ʼλ�ã����ں���)
int findSQLIST(SQLIST sqlist,SLDATA data,int begin,bool (*equal)(SLDATA,SLDATA));
//����
void sortSQLIST(SQLIST sqlist,bool increase,bool (*greater)(SLDATA,SLDATA));


#endif