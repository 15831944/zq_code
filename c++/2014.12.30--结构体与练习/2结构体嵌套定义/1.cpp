#include<iostream>

//�˴�������һ���ṹ����������_ABC���˺�Ĵ���
//�оͿ��԰�_ABC����һ��������ʹ��
struct _ABC
{
	char u;
	short i;
	int o;
};//u,i,o��Ϊ_ABC���͵ĳ�Ա����

struct _DEF
{
	_ABC j;//�ṹ�����͵�Ƕ�׶���
	double k;
};

void main()
{
	_DEF x;
	x.j.u = 1;
	x.j.i = 2;
	x.j.o = 3; 
	x.k = 4.0;
	std::cout<<sizeof(x)<<std::endl;
	system("pause");
}
