#include <iostream>

//malloc���ʧ�ܾͷ���0
//new���ʧ�ܽ����׳�һ��std::bad_alloc�쳣

void* operator new (size_t size, const char* s)
{
	return malloc(size);
}

void main()
{
	//����ѱ��ƻ��ˣ��������û���ڴ��ˣ���ô�׳�std::bad_alloc�쳣
	//new int;

	//����ѱ��ƻ��ˣ��������û���ڴ��ˣ���ô�����ʽ�Ľ��Ϊ0���ǲ����쳣
	//new (std::nothrow) int; //����������new�����

	int* p = new ("123abc") int;

	system("pause");
}