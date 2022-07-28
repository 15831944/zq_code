#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

//�ص��ı���ʵ�־��Ǻ���ָ�룬���ֻص�����������������
//�Լ�ȥ���ã�������д��Щ������ַ������������ȥ���ã�
//������Ϣ�������ǵ��͵Ļص�ʹ�÷�ʽ����Ϊ�����ṩWinProc
//��WNDCLASS����һ��������Ϣ��ôϵͳ��ȥ����WinProc������

//�ٱ������������������������ʱ����ʲô�������޷�Ԥ֪
//�ģ���ô����ͨ����д����ָ������������ʵ�б���
struct NODE
{
	int data;
	NODE* left;
	NODE* right;
};
void pre_travel(NODE* p, void (* do_something)(int* data))
{
	if (p)
	{
		(*do_something)(&p->data);
		pre_travel(p->left, do_something);
		pre_travel(p->right, do_something);
	}
} //pre_travel���ڻص�do_something

void print_node(int* data)
{
	std::cout<<*data<<" ";
}
void add_node(int* data)
{
	*data += 1;
}

void pre_travel2(NODE* p, void (* do_something)(int* data, void* parm), void* parm)
{
	if (p)
	{
		(*do_something)(&p->data, parm);
		pre_travel2(p->left, do_something, parm);
		pre_travel2(p->right, do_something, parm);
	}
}
void add_node(int* data, void* p)
{
	*data += *((int*)p);
}

BOOL __stdcall f(HWND h, LPARAM p)
{
	if (h)
	{
		char buf[256] = {};
		GetWindowTextA(h, buf, 256);
		//std::cout<<buf<<std::endl;
		std::vector<std::string>* q = (std::vector<std::string>*)p;
		q->push_back(std::string(buf));
	}

	return true;
}

void main()
{
	NODE n1 = {1};
	NODE n2 = {2};
	NODE n3 = {3};
	NODE n4 = {4};
	NODE n5 = {5};
	NODE n6 = {6};
	n1.left = &n2;
	n1.right = &n3;
	n2.left = &n4;
	n4.left = &n5;
	n4.right = &n6;

	//pre_travel(&n1, print_node); std::cout<<std::endl;
	//pre_travel(&n1, add_node);
	//pre_travel(&n1, print_node); std::cout<<std::endl;

	int x = 5;
	pre_travel2(&n1, add_node, &x);

	pre_travel(&n1, print_node); std::cout<<std::endl;

	//EnumWindows(void (* cl)(HWND hwnd))
	//for (�������еĴ��ھ��)
	//  (* cl)(hwnd);

	std::vector<std::string> v;
	EnumWindows(f, (LPARAM)&v);
	
	system("pause");
}