#include <iostream>
#include <assert.h>

class A
{
public:
	//һ�������з��ų�������ô�����ͱ���д
	//���죬����Ҫ�ڹ�����ʹ�ó�Ա��ʼ���б�
	//ȥ����Щ���ų������г�ʼ��
	const int a;
	A():a(1) //��ʼ��
	{
		//a = 1; //��ֵ
	}

	int b;

	void f1()
	{
		b = 1;
		int x = b;
	}

	//������Ա���������ֺ�������
	//���ܶԳ�Ա��������д�����
	void f2() const
	{
		//b = 1; //������
		int x = b; //����
	}
};

void main()
{
	A x;
	
	system("pause");
}