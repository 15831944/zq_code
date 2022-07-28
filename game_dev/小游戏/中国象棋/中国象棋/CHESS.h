#ifndef _CHSEE_H_
#define _CHESS_H_
//�췽������
#define _HF 0
#define _LF 1
//����������Ԫ��
#define L_JIANG 1
#define L_SHI 2
#define L_XIANG 3
#define L_MA 4
#define L_JU 5
#define L_PAO 6
#define L_BING 7
//ѡ������
#define _XZ 8
//�췽����Ԫ��
#define H_SHUAI -1
#define H_SHI -2
#define H_XIANG -3
#define H_MA -4
#define H_JU -5
#define H_PAO -6
#define H_BING -7
#define QP_W 9
#define QP_H 10
#define QP_S (QP_W)*(QP_H)
#define IN_QP(x,y) ((x) >= 0 && (x) < QP_W && (y) >= 0 && (y) < QP_H) 
//��������
extern int qp[QP_S];
//��ǰ���巽
extern char qz;
//˧�ͽ������ӹ���
bool wang(int b_x,int b_y,int e_x,int e_y);
//�˵����ӹ���
bool shi(int b_x,int b_y,int e_x,int e_y);
//������ӹ���
bool xiang(int b_x,int b_y,int e_x,int e_y);
//������ӹ���
bool ma(int b_x,int b_y,int e_x,int e_y);
//�������ӹ���
bool ju(int b_x,int b_y,int e_x,int e_y);
//�ڵ����ӹ���
bool pao(int b_x,int b_y,int e_x,int e_y);
//�������ӹ���
bool bing(int b_x,int b_y,int e_x,int e_y);
//��ʼ������
void InitQp();
//��ȡ����
int *GetQp();
#endif