#include <iostream>

//template��ʾ����ĺ�����һ��ģ�庯��
//��Ȼ��<>���ùؼ���typename������һ��ģ
//�����T�����T����һ�����ͣ��ھ����
//��������ֵ����ʽ�������������оͿ���
//�����T�����ˣ�ģ�庯�����Ǻ�

template <typename T>
T Add(T a,T b)
{
	T c = a + b;
	return c;
}

//��ͨ�ĺ��������Ƿ���ö��ᱻ���벢������
//ģ�庯����������þͲ��ᱻ����,Ҳ���������.
//(��ʵ�ʵ������滻ģ�������ĵ���)

struct _ABC
{
	char a;
	short b;
	int c;
	_ABC operator + (const _ABC& that)
	{
		_ABC abc = {a + that.a, b + that.b,c + that.c};
		return abc;
	}
};

template <typename T1,typename T2>
void PrintTT(T1 t1,T2 t2)
{
	std::cout<<t1<<" "<<t2<<std::endl;
}

//template <typename T>
//void sortPX(T* p ....)
//{}
void main()
{
	int x = Add<int>(1,2);
	float y = Add<float>(1.0f,3.5f);

	_ABC t1 = {1,2,3};
	_ABC t2 = {4,5,6};

	_ABC t3 = Add<_ABC>(t1,t2);

	PrintTT<char,int>('a',15);
	//��ʹ��ģ�庯����ʱ�򣬺���������ʽ
	//������ǰ����<>������д�����Ǿ����
	//���ͣ�һ���������ֵ��ã���ô������
	//�������������Ǹ����͵İ汾�ĺ�����
	//ģ�庯��֧���κ����ͣ�ֻ��ʹ��ʱҪ
	//ע��������Ƿ�֧��ĳЩ����.
	system("pause");
}

