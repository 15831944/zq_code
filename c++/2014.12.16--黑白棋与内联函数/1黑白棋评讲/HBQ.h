#define _QP_W 8
#define _QP_H 8
#define _QP_S (_QP_W * _QP_H)

#define _KZ 0
#define _HZ 1
#define _BZ 2

extern char qp[_QP_S];
extern char c;//��ǰ����

//��ʼ��
void HBQ_Init();

//x,y����������д��󷵻�-2
//��ǰλ�ò������ӷ���-1
//���ӳɹ���û��ʤ������0
//���ӳɹ���ʤ������1
int HBQ_Play(int x,int y);