#include <iostream>
#include <windows.h>

void main()
{
	int* p = (int*)malloc(4);

	*p = 100; //64 00 00 00

	//�����ǽ�p��ָ����ڴ浥Ԫ����Ϊ����ʹ�ã�����
	//�����p�����޸ģ�p��Ȼָ���ǿ���ڴ�
	free(p); //һ��ָ���ͷ�����һ����Ҫ�������p = NULL;

	if (p)
		std::cout<<"û���ͷ�"<<std::endl;
	else
		std::cout<<"�ͷ��� "<<std::endl;
	
	system("pause");
}