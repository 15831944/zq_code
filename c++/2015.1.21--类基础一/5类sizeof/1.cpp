#include<iostream>

class XYZ1
{

};
class XYZ2
{
public :
	void f()
	{
		std::cout<<"Hello"<<std::endl;
	}
};

class XYZ3
{
public:
	char x;//[0]
	int z;//<1><2><3>[4][5][6][7]
	short y;//[8][9]<10><11>
};

class XYZ4
{
public:
	char x;
	int z;
	short y;
	void f()
	{
		std::cout<<"Hello"<<std::endl;
	}
};

//01)���������Զ�Ϊ����(û�г�Ա��������)
//���һ���޷�����Ҳû�����ֵ�char��Ա����
//02)��Ա����������sizeof��С
//03)��ĳ�Ա����Ҳ��ѭ�ڴ����ԭ��

void main()
{
	std::cout<<sizeof(XYZ1)<<std::endl;
	std::cout<<sizeof(XYZ2)<<std::endl;
	std::cout<<sizeof(XYZ3)<<std::endl;
	std::cout<<sizeof(XYZ4)<<std::endl;
	system("pause");
}
