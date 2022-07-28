#include <iostream> 
using namespace std;


int main()
{
	//auto�Ƶ�����
	//1.��������Ϊָ�������ʱ��auto���Ƶ�����ͳ�ʼ�����ʽ��������
	//��cv(const, volatile)�޶���������һ��
	//2.������Ϊָ�������ʱ,auto���Ƶ���������ֳ�ʼ�����ʽ��cv����

	auto a = 0;		//a->int, a���Ƶ�Ϊint
	auto b = &a;	//b->int*, auto���Ƶ�Ϊint*
	auto& c = a;	//c->int&, auto���Ƶ�Ϊint

	//d->int, auto���Ƶ�Ϊint,���ʽ��һ����������ʱ,auto���������������
	//ֱ���Ƶ�Ϊԭʼ��int����
	auto d = c;		

	//const auto���ڱ���ʱ���滻Ϊconst int
	const auto e = a;	//e->const int

	//���ʽ����const����ʱ,auto���const��������
	//ֱ���Ƶ�Ϊԭʼ��int����
	auto f = e;			//f->int

	//��auto������(ָ��Ҳ����)���ʱ��auto���Ƶ����������ʽ��const����
	const auto& g = a;	//g->const int&
	auto& h = g;		//h->const int&

	//auto�����ޣ�
	//1.�������ں�������,
	//���� void f(auto a = 1){}
	//2.�������ڷǾ�̬��Ա����
	//struct A
	//{
	//	auto a = 1;//������󣬲������ڷǾ�̬��Ա����
	//	static const auto x = 2;
	//};
	//3.�޷���������
	//int arr[10]={0};
	//int c[10] = arr;


	//decltype
	int x = 0;
	decltype(x) y = 1;	//y->int
	decltype(x + y) z = 0;//z->int
	
	const int& i = x;
	decltype(i) j = y;	//j->const int&

	const decltype(z)* p = &z;//*p->const int, p->const int*
	decltype(z)* pi = &z;//*pi->int, pi->int*
	decltype(pi)* pp = &pi;//*pp->int*, pp->int**

	//decltype(exp)�Ƶ�����
	//1.exp�Ǳ�ʶ��������ʱ��ʽ,decltype(exp)��exp������һ��
	//�����ǰ���������Ƶ�һ��,���ڱ�ʶ�����ʽ����,decltype��
	//�Ƶ�����ͺ�������������Ͷ���һ��,������������һ����������
	//Ҳ�����������
	//2.exp�Ǻ�������,decltype(exp)�ͷ���ֵ������һ��
	int& fun_int_r();	//��ֵ
	int&& fun_int_rr();	//xֵ(��ֵ����)
	int fun_int();		//����ֵ
	const int& fun_cint_r();	//��ֵ
	const int&& fun_cint_rr();	//xֵ
	const int fun_cint();		//����ֵ

	decltype(fun_int_r()) a1 = x;//a1->int&
	decltype(fun_int_rr()) b1 = 0;//a1->int&&
	decltype(fun_int()) c1 = 0;//c1->int
	decltype(fun_cint_r()) a2 = x;//a2->const int&
	decltype(fun_cint_rr()) b2 = 0;//b2->const int&&

	//����const int����Ϊ�������ص�Int��һ������ֵ�����ڴ���ֵ����
	//ֻ�������Ϳ���Я��cv�޶�����������һ����Ե�cv�޶�
	decltype(fun_cint()) c2 = 0;//c2->int

	//Foo��һ����
	//const Foo fun_cfoo();
	//decltype(fun_cfoo()) ff = Foo();//ff->const Foo

	//3.�������,��exp��һ����ֵ,��decltype(exp)��exp���͵���ֵ����
	//�����exp����һ��
	//�����ŵı��ʽ�ͼӷ�������ʽ
	//struct Foo{int x;};
	//const Foo foo = Foo();

	//decltype(foo.x) a = 0;	//a->int

	//foo.x��һ����ֵ,��֪���ű��ʽҲ��һ����ֵ,�����Ƶ�����3
	//decltype�Ľ������һ����ֵ����
	//decltype((foo.x)) b = a;	//b->const int&

	//
	//int n =0 , m = 0;
	//decltype(n + m) c = 0;	//c->int, ����3
	//decltype(n += m) d = c;	//d->int&, ����3



	////auto��decltype�Ľ��ʹ��
	//���ַ�ʽһ�����ڷ���ֵ�����������������������ȷ������ֵ���͵�����
	//int& foo(int& i);
	//float foo(float& f);

	//template <typename T>
	//auto func(T& val) ->decltype(foo(val))
	//{
	//	return foo(val);
	//}

	std::getchar();
	return 0;
}
