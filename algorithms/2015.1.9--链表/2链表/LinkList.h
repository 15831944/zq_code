#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_
#define LLDATA int

typedef struct _LINK_LIST
{
	LLDATA data;//����
	_LINK_LIST* next;//ָ����һ���ڵ��ָ��
}* LINKLIST;

//����
LINKLIST createLINKLIST();
//����(����)
void destroyLINKLIST(LINKLIST linklist);
//����(�������ݣ�λ��)
bool insertLINKLIST(LINKLIST linklist,LLDATA data,int pos);
//����(��������)
void pushLINKLIST(LINKLIST linklist,LLDATA data);
//ɾ��(����λ��)
bool eraseLINKLIST(LINKLIST linklist,int pos);
//���(����)
void clearLINKLIST(LINKLIST linklist);
//����(����)
int lengthLINKLIST(LINKLIST linklist);
//��ȡ(����λ��)
LLDATA* getLINKLIST(LINKLIST linklist,int pos);
//����(�������ݣ���ʼλ�ã���Ⱥ���)
int findLINKLIST(LINKLIST linklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA));
//����
void sortLINKLIST(LINKLIST linklist,bool increase,bool (*greater)(LLDATA,LLDATA));
#endif