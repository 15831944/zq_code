#include <iostream>
#include "SqStack.h"
//˳���v
//����v
//ӳ��v
//����v
//��v

//ģ��˳��� v
//ģ������ V
//
//ģ��˫������V

//ģ��ӳ�� V
//ģ�弯�� V
//ģ���� V

//ģ��˳��ջ V
//ģ��˳�����  V

//vector
//A��Ѱ·

//˳��ѭ������
//˳�����ȶ���

//������
//��ȫ������
//��������

//������(������)
//�����
//��ϣ��

void main()
{
	CSqStack<int> ssq;
	ssq.Push(1);
	ssq.Push(2);
	ssq.Push(3);
	ssq.Push(4);
	ssq.Push(5);
	int b;
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);
	ssq.Pop(&b);

	std::cout<<ssq.Length()<<std::endl;
	system("pause");
}

