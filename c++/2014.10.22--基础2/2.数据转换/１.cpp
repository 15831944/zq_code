#include <iostream>

//����ת��
//��ʽת��
//��ʽת��(ǿ��ת��)

//��ʽת��
//01��(��=���ߵ��������Ͳ�һ��ʱ)=�ұߵ����ջᱻת��Ϊ=��ߵ��������Ͳ���ֵ�����
//02)��������int�͵����ݲ������㣬���е��ֽ���С��int��
//���Ͷ��ᱻ������Ϊint���ٲ�������
//03)�ֽ����ٵĻᱻת��Ϊ�ֽ������
//04)���ȵ͵Ļᱻת��Ϊ���ȸߵ�

void main()
{
	int a = 1;

	int b = 3.14f;

	//int = double ->int = int
	b = 3.5;

	//int = float -> int = int
	b = 3.5f;

	//int = char + char -> int = int + int 
	int a1 = 'a' + 'b';

	double a2;

	//double = double + float->double = double + double
	a2 = 4.4 + 1.2f;

	//double = int + double->double = double + double
	a2 = 3 + 2.5;

	//double = int + float->double = float + float->double = double
    a2 = 3 + 3.14f;

	//double = float + double->double = double + double
	a2 = 3.14f + 2.58;

	//int = double + int->int = double + double->int = int
	int a3 = 1.2 + 3;// warning C4244: ����ʼ����: �ӡ�double��ת������int�������ܶ�ʧ����

	system("pause");
}