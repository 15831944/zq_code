#define _QP_W 8
#define _QP_H 8
#define _QP_S (_QP_W * _QP_H)

#define _XY(x,y) ((x) + (y) * _QP_W)
#define _XY_X(i) ((i) % _QP_W)
#define _XY_Y(i) ((i) / _QP_W)

#define _KZ 0
#define _HZ 1
#define _BZ 2

//����
extern char qp[_QP_S];
//��ʼ��
void Init();
//��Ϸ����
void Play(int x,int y);