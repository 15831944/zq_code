#include <iostream>
#include <windows.h>
#include <time.h>
#include <string> //std::string��
#include <string.h> //C���Կ��е��ַ�����غ�������������ͷ�ļ�������strlen��strcmp
#include <cstring> //C++��string.h�İ�װ
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "SqQueue.h"
#include "SqSet.h"
#include "SqMap.h"
#include "Hash.h"
#include "MaxHeap.h"
#include "BinaryTree.h"

//����
//{
	//˳���vector����
	//��ʽ��list����
	//˳����С̡�˳��ѭ������
	//˳��ջ��
	//˳�򼯺ϡ�
	//˳��ӳ���
	//˳���ϣ���
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

int add(char a, float b)
{
	return (int)a + (int)b;
}
int sub(char a, float b)
{
	return (int)a - (int)b;
}

int hash_func(char* key)
{
	return (key[0] + key[strlen(key) - 1]) % 256;
}

int hash_func2(std::string key)
{
	return (key[0] + key[key.length() - 1]) % 256;
}

#define _MAX_NUM 100000
int a[_MAX_NUM];
int b[_MAX_NUM];

void select_sort(int* p, int n)
{
	int num = n - 1;
	for (int i = 0; i < num; ++i)
	{
		int j = i;
		for (int k = j + 1; k < n; ++k)
		{
			if (p[j] < p[k])
				j = k;
		}
		if (j != i)
		{
			int t = p[i];
			p[i] = p[j];
			p[j] = t;
		}
	}
}

void main()
{
	_BTN<char>* bt1 = createBTN<char>(); bt1->data = 'A';
	_BTN<char>* bt2 = createBTN<char>(); bt2->data = 'B';
	_BTN<char>* bt3 = createBTN<char>(); bt3->data = 'C';
	_BTN<char>* bt4 = createBTN<char>(); bt4->data = 'D';
	_BTN<char>* bt5 = createBTN<char>(); bt5->data = 'E';
	_BTN<char>* bt6 = createBTN<char>(); bt6->data = 'F';
	_BTN<char>* bt7 = createBTN<char>(); bt7->data = 'G';

	insertBTN(bt1, bt2);
	insertBTN(bt1, bt3, false);
	insertBTN(bt2, bt4);
	insertBTN(bt2, bt5, false);
	insertBTN(bt4, bt6);
	insertBTN(bt6, bt7, false);

	//pre_printBTN(bt1); std::cout<<std::endl;
	//mid_printBTN(bt1); std::cout<<std::endl;
	//post_printBTN(bt1); std::cout<<std::endl;

	std::cout<<heightBTN(bt1)<<std::endl;
	std::cout<<heightBTN(bt2)<<std::endl;
	std::cout<<heightBTN(bt3)<<std::endl;

	eraseBTN(bt2);

	//srand((unsigned int)time(0));
	//for (int i = 0; i < _MAX_NUM; ++i)
	//	a[i] = b[i] = rand();

	//int t1 = GetTickCount(); //�õ�������ĿǰΪֹ�ĺ�����
	//select_sort(a, _MAX_NUM);
	//std::cout<<GetTickCount() - t1<<std::endl;

	//CMaxHeap<int> mh;
	//int t2 = GetTickCount(); //�õ�������ĿǰΪֹ�ĺ�����
	//for (int i = 0; i < _MAX_NUM; ++i)
	//	mh.Push(b[i]);
	//while (mh.Size() > 0)
	//{
	//	int t;
	//	mh.Front(&t);
	//	mh.Pop();
	//	//�����ڴ�������豸�������ݽ����Ĳ�������������
	//	//��ӡ����д�ļ�
	//	//std::cout<<t<<std::endl;
	//}
	//std::cout<<GetTickCount() - t2<<std::endl;

	//��������������������죬��ν���������
	//�ڴ��е��������򣬻�����������Ҫ����ָ����
	//����е�����

	////s.

	////assert���������д�κ�һ���н���ı��ʽ����
	////������ʽ�Ľ��Ϊ�棬��ʲô���������������
	////���ʽ�Ľ��Ϊ�٣���ϵͳֱ��ǿ��ʹ��exit�˳�
	////���򲢸�����ϸ�ĳ�����Ϣ��assert��֮Ϊ���ԣ�
	////�������ڵ���
	////assert(0);

	////int a = 0;
	////++a = 1; //ǰ���������ʽ�Ľ�����Է���=��࣬Ҳ����˵ǰ���������ʽ�Ľ������һ������
	////a++ = 1; //�����������ʽ�Ľ�����ܷ���=��࣬Ҳ����˵�����������ʽ�Ľ������һ����������һ����ʱ��

	//CLinkList<int> sqlist1;
	//sqlist1.Push_Back(1);
	//sqlist1.Push_Back(2);
	//sqlist1.Push_Back(3);
	//sqlist1.Push_Back(4);

	////˳����������������൱���±���б���������
	////for (int i = 0; i < sqlist1.Size(); ++i)
	////{
	////	int* p = sqlist1.At(i);
	////	std::cout<<*p<<std::endl;
	////}

	//CLinkList<int>::Iterator it;

	//for (it = sqlist1.Begin(); it != sqlist1.End(); )
	//{
	//	if (*it == 3)
	//		it = sqlist1.Erase(it);
	//	else
	//		++it;
	//}
	//
	//for (it = sqlist1.Begin(); it != sqlist1.End(); ++it)
	//{
	//	std::cout<<*it<<std::endl;
	//}

	//CSqQueue<int> s;
	//s.Push(1);
	//s.Push(2);
	//s.Push(3);
	//s.Push(4);
	//while (!s.Empty())
	//{
	//	int data;
	//	s.Front(&data);
	//	s.Pop();
	//	std::cout<<data<<std::endl;
	//}

	//CMap<int, char> map;
	//map.Insert(0, 'A');
	//map.Insert(3, 'B');
	//map.Insert(2, 'D');
	//map.Insert(1, 'E');
	//map.Insert(-2, 'C');
	//for (int i = 0; i < map.Size(); ++i)
	//{
	//	std::cout<<map.At(i)->data<<std::endl;
	//}

	////ָ�����ݵ�ָ��
	////int* p = add;

	////ָ������ָ�룬pҪ�����ķ���ֵ
	////������int������ʽ�����������(char,float)
	//int (*p)(char, float) = add;

	//std::cout<<(*p)(1,2)<<std::endl;

	//p = sub;

	//std::cout<<(*p)(1,2)<<std::endl;

	////ͨ��С��������ж����������Ƿ����
	////int x, y;
	////std::cin>>x>>y;
	////if (!(x < y) && !(y < x))
	////	std::cout<<"���"<<std::endl;

	//CHash<char*, char> hash(hash_func);

	////����������û������ģ������ڲ���<�����
	////�����ǰ����ַ����ıȽϷ��򣬶��ǰ��յ�ַ
	////�Ĵ�С���бȽϵ�
	////hash.Insert("abc", 'x');
	////hash.Insert("def", 'y');
	////hash.Insert("cba", 'z');
	////hash.Insert("fed", 'w');
	////std::cout<<hash.Find("abc")->data<<std::endl;
	////std::cout<<hash.Find("def")->data<<std::endl;
	////std::cout<<hash.Find("cba")->data<<std::endl;
	////std::cout<<hash.Find("fed")->data<<std::endl;

	////����Ĵ����ǱȽϵ������ַ������泣���ĵ�ַ��С
	//if ("abc" > "def")
	//{
	//	std::cout<<"abc > def"<<std::endl;
	//}
	////����Ĵ����ǱȽϵ������ַ������泣�������ݴ�С
	//if (strcmp("abc", "def") == 1)
	//{
	//	std::cout<<"abc > def"<<std::endl;
	//}

	////C���Ա�����ɨ�赽�ַ������泣������������˶��
	////��ͬ���ַ������泣������ô���ַ����һ����
	//char* p1 = "123abc";
	//char* q1 = "123abc"; //���p1��q1���õ���ͬ�ĵ�ַ
	//char* r1 = "123" "abc"; //���������Զ���������д�����ַ������泣��

	////���Ҫ�������ַ��������ݱȽϷ��������в��봦������
	////ʹ��std::string��ΪKEYֵ
	//CHash<std::string, char> hash2(hash_func2);

	////std::string����д��[]�������
	//std::string x = "abc";
	//std::cout<<x[0]<<std::endl;
	//std::cout<<x[1]<<std::endl;
	//std::cout<<x[2]<<std::endl;

	


	system("pause");
}