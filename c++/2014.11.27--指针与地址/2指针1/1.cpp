#include<iostream>

//*
//乘法运算符:A * B
//解引用运算符(取变量)
//*A : A必须是一个地址
//则*A是A地址上的那个变量
//这个变量必须是和A地址的数据类型是一致


//&
//逻辑与 && :A&&B
//位与： A&B
//取地址运算符
//&A: A必须是一个变量
//则&A是A这个变量所开辟的内存区
//的首地址，这个地址的类型和A变
//量的类型是一致的

void main()
{
	int a = 1;

	//在内存中开辟了4个字节的内存区并命名为b
	//b是一个int类型的指针(指针是一种存储地址的变量,
	//int类型的指针只能存int类型的地址)
	int* b;

	//将a的首地址(int类型的地址)赋值给b指针(int类型的指针)
	//int类型的指针 = int类型的地址
	b = &a;

	//将b指针存储的地址上面的int变量赋值为2
	*b = 2;

	std::cout<<a<<std::endl;

	std::cout<<b<<std::endl;
	std::cout<<&a<<std::endl;

	//根据上面的代码可以得到以下结论
	//X类型 a;
	//X类型* b = &a;
	//*b就是a

	//int类型的指针 = int* 类型的地址
	//int* c = &b;

	//int*类型的指针 = int*类型的地址
	//在内存中开辟了4个字节的内存区，并取名为
	//c，c是一个int*类型的指针，可以存储int*类型的地址
	int** c = &b;//二级指针

	//*c是b，**c就是*b,**c就是a
	**c = 3;

	std::cout<<a<<std::endl;
	
	system("pause");
}