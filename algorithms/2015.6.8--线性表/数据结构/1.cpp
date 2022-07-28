#include <iostream>
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "SqQueue.h"
#include "SqSet.h"
#include "SqMap.h"

//����
//{
	//˳���vector����
	//��ʽ��list����
	//˳����С̡�˳��ѭ������
	//˳��ջ��
	//˳�򼯺ϡ�
	//˳��ӳ���
	//˳���ϣ��
//}

//����
//{
	//˳������
	//��ʽ��
	//��ʽ������
	//������
	//AVL��
	//�������set��map��
//}

//����
//{
//	�ڴ��
//}

//�㷨
//����ð�ݡ̡�ѡ��̡����ѡ����١��鲢
//���ң��۰�̡�KMP
//Ѱ·����ȡ���ȡ�A��

class ZuoBiao
{
	int x, y;
public:
	ZuoBiao& operator ++()
	{
		++x;
		++y;
		return *this;
	}
	ZuoBiao operator ++(int)
	{
		ZuoBiao zb = *this;
		++x;
		++y;
		return zb;
	}
};

#include <assert.h>

class A
{
public:
	class B
	{};
};
A::B f1()
{
	A::B b;
	return b;
}

//���һ����������һ��ģ�����е��࣬��ô�������ֵǰ��������typename

template <typename T>
class C
{
public:
	class D
	{};
};
template <typename T>
typename C<T>::D f2()
{
	C::D d;
	return d;
}

#include <stack>
#include <queue>

void main()
{
	//s.

	//assert���������д�κ�һ���н���ı��ʽ����
	//������ʽ�Ľ��Ϊ�棬��ʲô���������������
	//���ʽ�Ľ��Ϊ�٣���ϵͳֱ��ǿ��ʹ��exit�˳�
	//���򲢸�����ϸ�ĳ�����Ϣ��assert��֮Ϊ���ԣ�
	//�������ڵ���
	//assert(0);

	//int a = 0;
	//++a = 1; //ǰ���������ʽ�Ľ�����Է���=��࣬Ҳ����˵ǰ���������ʽ�Ľ������һ������
	//a++ = 1; //�����������ʽ�Ľ�����ܷ���=��࣬Ҳ����˵�����������ʽ�Ľ������һ����������һ����ʱ��

	CLinkList<int> sqlist1;
	sqlist1.Push_Back(1);
	sqlist1.Push_Back(2);
	sqlist1.Push_Back(3);
	sqlist1.Push_Back(4);

	//˳����������������൱���±���б���������
	//for (int i = 0; i < sqlist1.Size(); ++i)
	//{
	//	int* p = sqlist1.At(i);
	//	std::cout<<*p<<std::endl;
	//}

	CLinkList<int>::Iterator it;

	for (it = sqlist1.Begin(); it != sqlist1.End(); )
	{
		if (*it == 3)
			it = sqlist1.Erase(it);
		else
			++it;
	}
	
	for (it = sqlist1.Begin(); it != sqlist1.End(); ++it)
	{
		std::cout<<*it<<std::endl;
	}

	CSqQueue<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	while (!s.Empty())
	{
		int data;
		s.Front(&data);
		s.Pop();
		std::cout<<data<<std::endl;
	}

	CMap<int, char> map;
	map.Insert(0, 'A');
	map.Insert(3, 'B');
	map.Insert(2, 'D');
	map.Insert(1, 'E');
	map.Insert(-2, 'C');
	for (int i = 0; i < map.Size(); ++i)
	{
		std::cout<<map.At(i)->data<<std::endl;
	}

	system("pause");
}