#include<iostream>

//��
//#define �滻�ı�������
//01)���滻�ı��ĺ�
//02)���滻�ı��Ĵ��κ�
//03)�����滻�ı��ĺ�

//��C ,C++�����У���һ�ֺ�����Ĵ��ڣ�������#��ͷ
//#includeҲ�Ǻ�����������ǰ���ͷ�ļ�
//01)���滻�ı��ĺ�
//�˴�������һ����XYZ�����滻�ı�Ϊ100
//��֮��Ĵ����У�ֻҪ������XYZ���ᱻ�滻Ϊ100
#define XYZ 100

//�˴�������һ����ABC�����滻�ı�ΪXYZ + XYZ
//��֮��Ĵ����У�ֻҪ������ABC���ᱻ�滻ΪXYZ + XYZ
#define ABC  XYZ + XYZ

//�˴�������һ����ZanTing�����滻�ı�Ϊsystem("pause")
//��֮��Ĵ����У�ֻҪ������ZanTing���ᱻ�滻Ϊsystem("pause")
#define ZanTing system("pause")

//03)�����滻�ı��ĺ�
//�˴�������һ����DEF����û���滻�ı�
//��֮��Ĵ����У�������DEF���൱��ʲô��û��
#define DEF 

//02)���滻�ı��Ĵ��κ�
//�˴�������һ�����κֻ꣬Ҫ������ADD(?,!)�ĵط����ᱻ
//�滻Ϊ��+ !
#define ADD(a,b)  a + b

//�˴�������һ�����κֻ꣬Ҫ������BOOLL(?,!)�ĵط����ᱻ
//�滻Ϊ��== !
#define BOOLL(a,b) a == b

#define MAP_W 20
#define MAP_H 20
#define MAP   MAP_W * MAP_H

#define _KD 0 
#define _SD 1
#define _BJ 3
#define _Hero 2


void main()
{
	//int a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	//a = 200;
	int a = XYZ;
	a = ABC;
	std::cout<<a<<std::endl;
	//system("pause");
	ZanTing;

	DEF;

	int b = 15;

	int c = ADD(a,b);

	std::cout<<c<<std::endl;
	ZanTing;

	c = BOOLL(a,b);

	std::cout<<c<<std::endl;

	ZanTing;

	int map[MAP];
}