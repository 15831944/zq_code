#include <iostream>

//���ǳ�����ѭ������������

void main()
{
	int a[5];

	//std::cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];

	for (int i = 0; i < 5; ++i)
		std::cin>>a[i]; //i�ı仯0~4�����������Ч��Χ

	for (int i = 0; i < 5; ++i)
		std::cout<<a[i]<<' ';

	system("pause");
}