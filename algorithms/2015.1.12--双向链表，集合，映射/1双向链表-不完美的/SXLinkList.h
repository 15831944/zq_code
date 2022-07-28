#ifndef _SX_LINK_LIST_H_
#define _SX_LINK_LIST_H_
#define LLDATA int

typedef struct _SXLINK_LIST
{
	LLDATA data;//����
	_SXLINK_LIST* next;//ָ����һ���ڵ��ָ��
	_SXLINK_LIST* pre;//ָ��ǰ��һ���ڵ��ָ��
}* SXLINKLIST;

//����
SXLINKLIST createSXLINKLIST();
//����(����)
void destroySXLINKLIST(SXLINKLIST sxlinklist);
//����(�������ݣ�λ��)
bool insertSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int pos);
//����(��������)
void pushSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data);
//ɾ��(����λ��)
bool eraseSXLINKLIST(SXLINKLIST sxlinklist,int pos);
//���(����)
void clearSXLINKLIST(SXLINKLIST sxlinklist);
//����(����)
int lengthSXLINKLIST(SXLINKLIST sxlinklist);
//��ȡ(����λ��)
LLDATA* getSXLINKLIST(SXLINKLIST sxlinklist,int pos);
//����(�������ݣ���ʼλ�ã���Ⱥ���)
int findSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA));
//����
void sortSXLINKLIST(SXLINKLIST sxlinklist,bool increase,bool (*greater)(LLDATA,LLDATA));
#endif