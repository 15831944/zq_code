#ifndef _1_H_
#define _1_H_

template <typename T>
class p
{
	T t;
public:
	void f() //ģ�����е���������
	{
		t = 0;
		std::cout<<t<<std::endl;
	}
	void ff();
};

template <typename T>
void p<T> ::ff()//ģ�����е���ͨ��Ա������ֱ�ӽ�����д��ͷ�ļ���
{
	t = 0;
	std::cout<<t<<std::endl;
}

#endif