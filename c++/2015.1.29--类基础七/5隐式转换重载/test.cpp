#include <iostream>

class A 
{
	int a;
public:
	A(int aa)
		:
	a(aa)
	{}


	//��ʽת��
	//operator Ŀ������()
	operator int()
	{
		return a;
	}

	operator const char*()
	{
		return "123abc";
	}
};

void main()
{
	A x(100);
	int y;
	y = x;

	const char* p = x;
	system("pause");
}

//���������ʽת�������ر����϶��Ǻ���
//����ʽ�������˸����ǹ涨�õģ�������
//�������������������䷵��ֵҲ������
//�������ã�����̫���,���Բ��Ƽ�ʹ������
//�����ء�
//������ѧ��������бȽ��ʺ�ʹ�����������

 