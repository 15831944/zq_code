#include <iostream>

//���������ͬ�ำֵ������
//һ����˵����һ�����������
//��������һ�����������
//����˵���ǿ����е��Ǹ������
//��¡����,�Ϳ��Է�װΪ���������
//ͬ�ำֵ��

//����Ҫ���ؿ��������ͬ�ำֵ����ΪA1��
//��û��ָ��ָ��ͬһƬ���ڴ������.
class A1
{
public:
	int a1;
};

class A2 
{
	int* a2;
public:
	A2(int b)
	{
		a2 = new int;
		*a2 = b;
	}

	A2(const A2& that)
	{
		a2 = new int;
		*a2 = *(that.a2);
	}

	A2& operator = (const A2& that)
	{
		if(this != &that)
		{
			*a2 = *(that.a2);
		}
		return *this;
	}
	void Set()
	{
		*a2 = 1;
	}

	~A2()
	{
		delete a2;
	}
};

void main()
{
	//A1 x1;
	//x1.a1 = 1;
	//A1 x2 = x1;//Ĭ�Ͽ�������
	//x1 = x2 ;//Ĭ��ͬ�ำֵ
	
	A2 x1(4);
	{
	A2 x2 = x1;
	}
	x1.Set();
	system("pause");
}
