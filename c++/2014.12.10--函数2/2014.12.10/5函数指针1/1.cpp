#include<iostream>
//�ݹ�
//������Ĭ�ϲ���
//����������
//����ָ��

int add2(int a,int b)
{
	return a + b;
}
int add3(int a,int b,int c)
{
	return a + b + c;
}
int  sub2(int a,int b)
{
	return a - b;
}

void f(const char* p)
{
	std::cout<<p + 1<<std::endl;
}
void main()
{
	//����ֵ���� ����ָ���� ����ʽ������(ֻд��������)��;
	void (*q)(const char*) = 0;
	q = f;
	(*q)("asdff");
	//void* q1 = f;
	//int* q2 = sub2;
	//01)�������Ǻ������׵�ַ
	//02)ָ�������ָ���ǲ���ָ������
	//03)voidָ���ǿ���ָ�����ģ���û����

	//���е�ָ�������ָ��(����voidָ��)������ָ����
	//voidָ���ǿ���ָ�����ģ���û����

	int (*p)(int,int) = add2;
	//add2�ķ���ֵ����ʽ���������p��Ҫ��
	//����ָ�� = ������
	p = sub2;
	//sub2�ķ���ֵ����ʽ���������p��Ҫ��

	//p = add3;
	//add3�ķ���ֵ����ʽ����������p��Ҫ��

	//*����ָ��ͱ�ʾ��ָ��ĺ���
	std::cout<<(*p)(1,2)<<std::endl;//�൱��sub2(1,2)

	p = add2;
	std::cout<<(*p)(1,2)<<std::endl;//�൱��add2(1,2)

	//����ָ�������ͬһ�������ɲ�ͬ�Ĺ���(��̬)


	//����ָ������
	int (*r[3])(int,int) = {p,sub2,r[1]};
	//r[0] = p,r[1] = sub2; r[2] = r[1];
	std::cout<<(*r[0])(1,2)<<std::endl;//3
	std::cout<<(*r[1])(1,2)<<std::endl;//-1
	std::cout<<(*r[2])(1,2)<<std::endl;//-1
	system("pause");
}