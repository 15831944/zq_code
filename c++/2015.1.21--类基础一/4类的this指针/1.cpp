#include<iostream>

class XYZ
{
public:
	char x;
	short y;
	int z;
	void f(char X,short Y,int Z)
	{
		this->x = X;
		y = Y;
		z = Z;
	}
	void h()
	{
		std::cout<<x<<" "<<y<<" "<<z<<std::endl;
	}
};

//���ڴ����Ա������ʱ����������ı仯�������������
//�����������ͱ�Ϊ
//void f(XYZ* this,char X,short Y,int Z)
//{
//	this->x = X;
//	this->y = Y;
//	this->z = Z;
//}
//void h(XYZ* this)
//{
//	std::cout<<this->x<<" "<<this->y<<" "<<this->z<<std::endl;
//}

//��Ա�������ᱻ����һ�����ص���ʽ�����������ʽ���������ֽ�this,
//�����Ǳ����ָ�룬Ȼ���ڳ�Ա�����е����г�Ա����֮ǰ������this->

//void main()
//{
//	XYZ a;
//	a.f('q',1,2);//f(&a,'q',1,2)
//	a.h();//h(&a)
//
//	XYZ b;
//	b.f('p',3,4);//f(&b,'q',1,2)
//	b.h();//h(&b)
//	system("pause");
//}

//�������ڴ��������XYZ��ʱ��
//��ű����������ӣ�һ���ṹ�����һ�麯����
//��Щ�����ĵ�һ��������������ṹ���ָ�룬
//�ɼ���Ա�����ı��ʾ���һ����ͨ������ֻ����������
//�Զ�Ϊ�����thisָ�롣ʹ֮���õ�ʱ�������

struct XYZ2
{
	char x;
	short y;
	int z;
};

void f(XYZ2* thiss,char X,short Y,int Z)
{
	thiss->x = X;
	thiss->y = Y;
	thiss->z = Z;
}
void h(XYZ2* thiss)
{
	std::cout<<thiss->x<<" "<<thiss->y<<" "<<thiss->z<<std::endl;
}

void main()
{
	XYZ2 a;
	f(&a,'q',1,2);
	h(&a);

	XYZ2 b;
	f(&b,'p',3,4);
	h(&b);
	system("pause");
}