#include "WZQ.h"

int CWZQ::_ZX(int x,int y)
{
	return x + y * _QPW;
}

void CWZQ::Init()
{
	for(int i = 0; i < _QPS;++i)
		qp[i] = _KZ;
	c = _HZ;
}

//�����ж�
//_ER : ���ӳ�������ڸ�λ������
//_KZ : û��ʤ��
//_HZ : ����ʤ��
//_BZ : ����ʤ��

int CWZQ::LuoZi(int x,int y)
{
	if(x < 0 || x > _QPW - 1 
	|| y < 0 || y > _QPH - 1
	|| qp[_ZX(x,y)] != _KZ)
		return _ER;

	qp[_ZX(x,y)] = c;
	for(int i = 0; i < 5 ;++i)
	{
	
	}
	c = (c == _HZ) ? _BZ : _HZ;
	return _KZ;
}

//��ȡ���̵�����(������ʾ)
const char* CWZQ::getqp()
{
	return qp;
}

//�õ���ǰ���ӵ���ɫ
char CWZQ::getc()
{
	return c;
}