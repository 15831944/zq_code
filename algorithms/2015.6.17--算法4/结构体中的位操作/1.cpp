#include <iostream>

struct ABC
{
	//a��һ��ռ2λ���з���������-2~1��
	//b��һ��ռ4λ���з���������-8~7��
	char a : 2, b : 4;
};

struct DEF
{
	//a��һ��ռ3λ���޷���������0~7��
	//b��һ��ռ11λ���޷���������0~2047��
	unsigned short a : 3, b : 11; //���е�ռλ�Ͳ��ܳ���sizeof(����)
	//c��һ��int����
	int c;
	//d��һ��ռ30λ���з���������0~2047��
	int d : 30;
};

struct XYZ1
{
	unsigned short a : 3, b : 13;
	//[b][b][b][b][b][a][a][a]
	//[b][b][b][b][b][b][b][b]
};

struct XYZ2
{
	unsigned short a : 3, b : 14;
	//[b][b][b][b][b][a][a][a]
	//[b][b][b][b][b][b][b][b]
	//[b][?][?][?][?][?][?][?]
	//[?][?][?][?][?][?][?][?]
};

void main()
{
	ABC abc;
	abc.a = -2;
	abc.a = 1;
	abc.a = 2;
	abc.b = 2;
	std::cout<<sizeof(ABC)<<std::endl;

	DEF def;
	def.a = 0;
	def.a = 7;
	def.a = 8;
	def.b = 2047;

	std::cout<<sizeof(XYZ1)<<std::endl;
	std::cout<<sizeof(XYZ2)<<std::endl;

	system("pause");
}