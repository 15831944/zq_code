#include "HBQ.h"

#define _XY(x,y) ((x) + (y) * _QP_W)
#define _XY_X(i) ((i) % _QP_W)
#define _XY_Y(i) ((i) / _QP_W)

#define _IN_QP(x,y) ((x) >= 0 && (x) < _QP_W && (y) >= 0 && (y) < _QP_H) 

char qp[_QP_S];
char c;

//����true��ʾ��������
//����false��ʾ����������
//changeֻ�п�������ʱ������
//changeΪ��ͰѼ�ס�����Ӹı���ɫ
//changeΪ���򲻸ı��ס�����Ӹı���ɫ
bool HBQ_LuoZi(int x,int y,bool change)
{
	//
	char lz = 0;
	//����仯��ƫ����
	//�ϣ����ϣ��ң����£��£����£�������
	const int xbh[] = {0,1,1,1,0,-1,-1,-1};
	const int ybh[] = {-1,-1,0,1,1,1,0,-1};

	for(int i = 0;i < 8;++i)
	{
		bool zd = false;
		int x2 = x + xbh[i] * 2;
		int y2 = y + ybh[i] * 2;
		for(;_IN_QP(x2,y2);x2 += xbh[i],y2 += ybh[i])
		{
			if(qp[_XY(x2,y2)] == c)
			{
				zd = true;
				break;
			}
		}

		if(zd)
		{
			//�õ��Է���ɫ
			char cc = (c == _HZ ? _BZ:_HZ);
			//��ɫ
			bool bs = true;
			//ѭ���ж�
			x2 -= xbh[i];
			y2 -= ybh[i];
			int x3 = x2,y3 = y2;
			for(;x2 != x || y2 != y;x2 -= xbh[i],y2 -= ybh[i])
			{
				if(qp[_XY(x2,y2)] != cc)
				{
					bs = false;
					break;
				}
			}
			if(bs)
			{
				//���ñ�����ļ��ӱ�־Ϊ��
				lz |= (1 << i); 
				//
				if(change)
				{
					for(;x3 != x || y3 != y;x3 -= xbh[i],y3 -= ybh[i])
						qp[_XY(x3,y3)] = c;
				}
			}
		}
	}
	if(lz && change)
	{
		qp[_XY(x,y)] = c;
		c = (c == _HZ ? _BZ:_HZ);
	}
	return lz != 0;
}

void HBQ_Init()
{
	//��ʼ������
	for(int i = 0; i < _QP_S;++i)
	{
		qp[i] = _KZ;
	}
	qp[_XY(3,3)] = qp[_XY(4,4)] = _HZ;
	qp[_XY(3,4)] = qp[_XY(4,3)] = _BZ;
	c =_HZ;
}

int HBQ_Play(int x,int y)
{
	//�����λ���Ƿ�Ϸ�
	if(!_IN_QP(x,y))
		return -2;
	//�����λ���Ƿ������ӣ������򷵻�-1
	if(!HBQ_LuoZi(x,y,false))
		return -1;
	//�������Ӿ͸���
	HBQ_LuoZi(x,y,true);
	for(int i = 0; i < _QP_S;++i)
	{
		if(qp[i] == _KZ)
			return 0;
	}
	return 1;
}