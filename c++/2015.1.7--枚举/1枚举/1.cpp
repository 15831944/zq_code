#include<iostream>

//union _ABC
//{
//	int a;
//	short b;
//	double c;
//};

//ö�� enum

//ö����һ�����ͼ���ȡֵ��Χ
//ö�ٵı�����int
//ȡֵ�����ǺϷ��ı�ʶ��

enum _ABC
{
	abc1, //0 �����ȡֵ�ᱻ����Ϊ0�������ȡֵ
	abc2, //1 ���ε���
	abc3, //2
	abc4  //3
};

void main()
{
	_ABC x = abc1;
	x = abc2;
	_ABC y = abc3;
	y = abc4;
	//y = 2;//��Ȼö�ٵı�����int�������ܱ�int��ֵ
	x = y;
	//x = x + y;//_ABC + _ABC ->��ʽת�� ��int+int
	
	x + y;//

	int b = sizeof(x);
	//++x;
	x && y;
	x == y; //������ö����Ҫʹ�õ������!!!!!!!!!
	x ? 1:2;
	1 ? x:y;
	x & y;
	//x += y;

	_ABC* z = &x;
	y = *z;
	_ABC t[3];
	t[0] = x;

	//��������Ϊ��

#define _KZ 0
#define _HZ 1
#define _BZ 2

	char qp1[400];

	qp1[0] = 3;//������Ը�ֵ��������Ϸ�Ƕ���˵�Ǵ���ģ���Ϊ��֪������ʲô����
	//���������ֲ����������

	enum _QIZI
	{
		_QI_KZ,
		_QI_HZ,
		_QI_BZ
	};

	_QIZI qp2[400];
	qp2[0] = _QI_KZ;
	qp2[1] = _QI_HZ;
	qp2[2] = _QI_BZ;
	//qp2[2] = 3;//����ö����ǿ��Լ�����ǵ����Ϳ��Ա�����ֵ��
	system("pause");
}