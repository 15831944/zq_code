#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#define BTDATA int

typedef struct _BINARY_TREE
{
     BTDATA data;
     _BINARY_TREE* parent;
     _BINARY_TREE* left;
     _BINARY_TREE* right;
}* BINARYTREE;

//����
BINARYTREE createBINARYTREE();

//�Ͽ������丸�ڵ����ϵ
BINARYTREE cutBINARYTREE(BINARYTREE bt);

//����:��bt2����bt1��leftΪ�����ߣ��ٲ��ұ�
BINARYTREE insertBINARYTREE(BINARYTREE bt1,BINARYTREE bt2,bool left);

//ɾ��
void deleteBINARYTREE(BINARYTREE bt);

//����
int  countBINARYTREE(BINARYTREE bt);

//�߶�
int heightBINARYTREE(BINARYTREE bt);


#endif