#include <iostream>

//��֪������TestLib.libҪ���뱾���̵�����
#pragma comment(lib, "TestLib.lib")

//�������Щ�����Ķ��嶼��TestLib.lib������ֻ��
//�ö��޷��鿴��Դ����
extern int a;
extern int x;
void b();
void y();

void main()
{
	a = 1;
	b();
	x = 2;
	y();

	system("pause");
}