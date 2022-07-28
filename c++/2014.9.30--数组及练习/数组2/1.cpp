#include <iostream>

void main()
{
	//单个变量的定义并初始化
	int a = 1;

	//数组的初始化1   !!!!
	//在数组后面加上={},{}中写上对应的数组元素
	//要被初始化的表达式,{}里面的表达式称之为数
	//组的初始化项,初始化的顺序是从下标[0]的元素
	//到下标[长度-1]的元素
	char b[5] = {'a', 'b', 99, 'd', 100 + a};

	//除了初始化的时候可以用{}为数组中的每个元素进行
	//初始化而外,其它任何时候不允许再用{}来为数组整体
	//赋值,数组定义完毕之后是无法整体赋值,定义完毕之后
	//使用数组其就是使用数组中的每个变量
	//b[5] = {'f', 'g', 'h', 'i', 'j'};
	//下面逐一为数组中每个元素赋值是允许的
	b[0] = 'f';
	b[1] = 'g';
	b[2] = 'h';
	b[3] = 'i';
	b[4] = 'j';

	char k[6];
	//f[6] = {'a', 'b', 99, 'd', 100 + a};错误的赋值


	//允许后面的元素的初始化用到前面的元素
	char c[5] = {'a', c[0] + 1, c[1] + 1, c[2] + 1, c[3] + 1};


	//数组初始化2
	//若初始化项的数量(加速为m)是小于数组的长度的话,则只会
	//初始化数组的前m个元素,后面的所有元素默认都被初始化为0
	float d[5] = {1.1f, 2.2f, 3.3f};

	//初始化项的数量可以小于等于数组长度,但是不能大于
	//数组长度
	//double e[3] = {1.1, 2.2, 3.3, 4.4};

	//若一个初始化项都不写,则数组中每个元素都会被初始化为0的  !!!!
	double f[5] = {};
	
	//数组初始化3
	//若定义数组并初始化的时候[]中不写表示数组长度的常量
	//表达式,则编译器会自动根据{}中的初始化项的数量来设置
	//数组的长度
	bool g[] = {true, false, true, true};//   !!!!
	//bool h[]; //若不用{}初始化,则[]中常量表达式不能省略

	system("pause");
}