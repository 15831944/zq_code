#include <iostream>
#include <conio.h>

#define _QP_W 20 //���̿�
#define _QP_H 20 //���̸�
#define _QP_S (_QP_W * _QP_H) //���̴�С
#define _YXZT_CSH 0 //��Ϸ״̬��ʼ��
#define _YXZT_YX 1 //��Ϸ״̬����
#define _KZ 0 //����
#define _HZ 1 //����
#define _BZ 2 //����
#define _ZX(x,y) ((x)+(y)*_QP_W) //����ת�±�
#define _XZx(i) ((i)%_QP_W) //�±�תx����
#define _XZy(i) ((i)/_QP_W) //�±�תy����

struct _WZQ
{
	char qp[100]; //��������
	short x : 6, y : 6, c : 1, yxzt : 1;
}; //cΪ0���ʾ��ǰ�º��ӡ�Ϊ1���ʾ��ǰ�°���

_WZQ wzq;

//������102���ֽ������������Ϸ