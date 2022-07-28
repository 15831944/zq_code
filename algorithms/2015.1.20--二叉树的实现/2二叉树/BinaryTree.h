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

//ǰ��--�ݹ�
void recursion_pre_travelBINARYTREE(BINARYTREE bt);
//����
void recursion_mid_travelBINARYTREE(BINARYTREE bt);
//����
void recursion_post_travelBINARYTREE(BINARYTREE bt);

//ǰ��---�ǵݹ�
void pre_travelBINARYTREE(BINARYTREE bt);
//����
void mid_travelBINARYTREE(BINARYTREE bt);
//����
void post_travelBINARYTREE(BINARYTREE bt);

//����--�ǵݹ�
void level_travelBINARYTREE(BINARYTREE bt);

#endif