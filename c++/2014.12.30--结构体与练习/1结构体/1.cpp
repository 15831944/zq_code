#include<iostream>

//�˴�������һ���ṹ����������_ABC���˺�Ĵ���
//�оͿ��԰�_ABC����һ��������ʹ��
struct _ABC
{
	char u;
	short i;
	int o;
};//u,i,o��Ϊ_ABC���͵ĳ�Ա����

void main()
{
	int x;
	x = 0;
	_ABC y;
	std::cout<<sizeof(y)<<std::endl;//8
	//ʹ�ýṹ��ʵ����ʹ�ýṹ���г�Ա����
	y.u = 1;
	y.i = 2;
	y.o = 3;
	
	system("pause");
}
//������һ����Ϸ����Ϸ��������һ���ˣ��������ǵ�����
//���£�
//  ʹ�û����������ʹ���
//  int hp[8],mp[8],att[8],def[8];
//  Ҫ��Ӣ�۽��и�ֵ
//  hp[0] = 100;mp[0] = 100;att[0] = 10;def[0] = 10;

//ʹ�ýṹ��
//struct _HERO
//{
//	int hp,mp,att,def;
//};
//
//_HERO hero[8];
//hero[0].hp = 100;
//hero[1].mp = 100;
//hero[2].att = 10;
//hero[3].def = 10;
