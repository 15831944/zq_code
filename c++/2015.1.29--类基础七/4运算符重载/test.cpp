#include <iostream>

class A
{
public:
	A& operator = (const A& that)
	{
		return *this;
	}
};

//���������
//01)�����ǵ���֧��ĳЩ�����ܽ��е�����
//02)��������ر����Ǻ���
//03)��4���������������: 
//.
//:: 
//?:
//sizeof
//04)��Ŀ���������ʽ��������Ϊ��
//   ���õ�++��--����ʽ������һ��
//   ��ʹ�õ�int
//05)˫Ŀ���������ʽ����ֻ����һ��

class ZuoBiao
{
public:
	int x,y;
	
	ZuoBiao(int X = 0,int Y = 0)
		:
	x(X),y(Y)
	{
	
	}

	//����������ķ���ֵһ����������͵���ʱ��
	//����������
	ZuoBiao operator + (const ZuoBiao& that)
	{
		//this + that
		ZuoBiao zb(x + that.x,y + that.y);
		return zb;
	}

	//��ֵ���Ը�ֵ������ķ���ֵһ����������͵�
	//���ã�Ӧ������*this

	ZuoBiao& operator += (const ZuoBiao& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	//ǰ��++
	ZuoBiao& operator ++()
	{
		++x;
		++y;
		return *this;
	}

	//����++
	//��ʽ������һ����ʹ�õ�int
	ZuoBiao operator ++(int)
	{
		ZuoBiao zb(x,y);
		++x;
		++y;
		return zb;
	}
	
	//����
	ZuoBiao operator -()
	{
		ZuoBiao zb(-x,-y);
		return zb;
	}


};

//- * / % 
//-= ,*= ,/=, %=
//--
//== != >= <= > < 
//&& || !

void main()
{
	ZuoBiao zb1(1,2),zb2(3,4);
	ZuoBiao zb3 = zb1+zb2;
	//+ Ĭ�Ͽ�������
	//ZuoBiao zb3 = zb1.operator +(zb2);
	//��ȫ��ͬ������Ĵ���

	zb3 += zb1;

	++zb3;

	ZuoBiao zb4 = zb3++;
	system("pause");
}
