#include <iostream>
#include <vector>
using namespace std;

//�ο����ϣ�http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
//	    http://www.cnblogs.com/hujian/archive/2012/02/13/2348621.html

void f1(int &r)
{
	cout << "��ֵ���ã�" << r << endl;
}

void f1(int &&r)
{
	cout << "��ֵ���ã�" << r << endl;
}

void f2(int &&r)
{
	f1(r);
}

class MyString 
{ 
private: 
	char* _data; 
	size_t   _len; 

//����
void _init_data(const char *s) 
{ 
	_data = new char[_len+1]; 
	memcpy(_data, s, _len); 
	_data[_len] = '\0'; 
} 

public: 

//�޲ι���
MyString() 
{ 
	_data = NULL; 
	_len = 0; 
} 

//���ι���
MyString(const char* p)
{ 
	_len = strlen (p); 
	_init_data(p); 
} 

//��������
MyString(const MyString& str) 
{ 
	_len = str._len; 
	_init_data(str._data); 
	std::cout << "�����˿�������: " << str._data << std::endl; 
} 

//ͬ�ำֵ
MyString& operator=(const MyString& str) 
{ 
	if (this != &str) 
	{ 
		_len = str._len; 
		_init_data(str._data); 
	} 
	std::cout << "������ͬ�ำֵ: " << str._data << std::endl; 
	return *this; 
} 

//ת�ƹ���
//�Ϳ������캯�����ƣ��м�����Ҫע�⣺
//��������ֵ���ķ��ű�������ֵ���÷��ţ�����&&����
//��������ֵ���������ǳ�������Ϊ������Ҫ�޸���ֵ��
//��������ֵ������Դ���Ӻͱ�Ǳ����޸ġ�������ֵ�����������ͻ��ͷ���Դ��ת�Ƶ��¶������ԴҲ����Ч��
MyString(MyString &&str)
{
	 std::cout << "������ת�ƹ���: " << str._data << std::endl; 
    _len = str._len; 
    _data = str._data; 
    str._len = 0; 
    str._data = NULL;
}

//ת�Ƹ�ֵ������
MyString& operator=(MyString&& str) 
{ 
    std::cout << "������ת�ƿ�������: " << str._data << std::endl; 
    if (this != &str) 
	{ 
      _len = str._len; 
      _data = str._data; 
      str._len = 0; 
      str._data = NULL; 
    } 
    return *this; 
 }

//����
virtual ~MyString() 
{ 
	if (_data) 
		free(_data); 
} 

}; 

template <typename T>
void myswap1(T& a, T& b)
{
	//���ｫ�������β���Ҫ�Ŀ�������
	T t = a;
	a = b;
	b = t;
}
template <typename T>
void myswap2(T& a, T& b)
{
	//������3�β���Ҫ�Ŀ�������
	T t = std::move(a);
	a = std::move(b);
	b = std::move(t);
}


void main()
{
	//��C++98�У�����һ����������ʼ��һ����ֵ��
	int a = 1;
	int &b = a;//����

	//���Ҫ��һ����ֵ����ʼ��һ������ʱ���ͱ����ǳ����ò��У�����
	//int &c = 1;//�����ԣ��޷���intת��Ϊint&
	const int &c = 1;//����

	//����C++11��Ϊ��������ֵ����ֵ���ֱ���&��&&�������������ֵ����ֵ������
	//ע�⣺����ֵ���õ�ʱ����ֵ�������ǳ�������Ϊ��Ҫ�ı�
	int d = 1;
	f1(d);	//���õ�f1����ֵ����
	f1(1);	//���õ�f1����ֵ����

	//���õ�f1����ֵ���ã��Ǵ���Ϳ��Կ�����֮ǰֻ��һ��2��������һ����ʱ����
	//Ҳ����һ����ֵ���ڶ���������ֵ���ù��󣬾ͱ������ֵ
	f2(2);  

	//��ΪʲôҪ��ô���أ���ֵ����������֧��ת������ġ�
	//ת��������Խ���Դ ( �ѣ�ϵͳ����� ) ��һ������ת�Ƶ���һ������
	//�����ܹ����ٲ���Ҫ����ʱ����Ĵ����������Լ����٣�
	//�ܹ��������� C++ Ӧ�ó�������ܣ���ʱ�����ά��( ���������� )������������Ӱ�졣
	//ͨ��ת�����壬��ʱ�����е���Դ�ܹ�ת�������Ķ����
	//�����е� C++ �����У����ǿ��Զ��忽�����캯���͸�ֵ������Ҫʵ��ת�����壬
	//��Ҫ����ת�ƹ��캯���������Զ���ת�Ƹ�ֵ��������������ֵ�Ŀ���	
	//�͸�ֵ�����ת�ƹ��캯����ת�Ƹ�ֵ�����������ת�ƹ��캯����ת�ƿ���������û�ж��壬
	//��ô����ѭ���еĻ��ƣ��������캯���͸�ֵ�������ᱻ���á�
	//��ͨ�ĺ����Ͳ�����Ҳ����������ֵ���ò�����ʵ��ת������

	//�����MyString(��Hello��) �� MyString(��World��) ������ʱ����Ҳ������ֵ��
	//��Ȼ��������ʱ�ģ���������Ȼ�����˿�������Ϳ�����ֵ�������û���������Դ������ͷŵĲ�����
	//����ܹ�ֱ��ʹ����ʱ�����Ѿ��������Դ�����ܽ�ʡ��Դ�����ܽ�ʡ��Դ������ͷŵ�ʱ�䡣
	//�����Ƕ���ת�������Ŀ��
	MyString s; 
	s = MyString("Hello");	//������ת�ƹ��캯��
	std::vector<MyString> vec; 
	vec.push_back(MyString("World")); //������ת�Ƹ�ֵ��������


	//��Ȼ������ֻ����ֵ���ò��ܵ���ת�ƹ��캯����ת�Ƹ�ֵ������
	//��������������ֻ������ֵ���ã������֪һ������������
	//��ʹ�ö����������ת�ƹ��캯����ת�Ƹ�ֵ������
	//Ҳ���ǰ�һ����ֵ���õ�����ֵ������ʹ�ã���ô���أ���׼���ṩ�˺��� std::move��
	//��������Էǳ��򵥵ķ�ʽ����ֵ����ת��Ϊ��ֵ���á�
	int a1 = 1;
	f1(a1);	//������f1����ֵ����
	f1(std::move(a1));//����std::moveת�����󣬾Ͱ�a1����ֵ���ñ������ֵ����

	//�Ǿ����������أ���������һ��swap������
	int t1 = 10;
	int t2 = 20;

	myswap1<int>(t1, t2);
	cout << t1 <<"  " << t2 << endl;  
	myswap2<int>(t1, t2);
	cout << t1 <<"  " << t2 << endl;  

	system("pause");
}