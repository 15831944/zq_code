#include <iostream>

//ǰ׺ + ���ͱ�� + ����
//ǰ׺
//ȫ�ֱ���(global:ȫ��ģ�ȫ�ֵ�):g_
//��Ա����(member:��Ա):m_
//���ų���(constant:�����):c_

//����
//������������
//bool:b
//char:c
//unsigned char :uc
//wchar_t:w
//short:s
//unsigned short:us
//int:i
//unsigned int :ui
//long:l
//unsigned long:ul
//float :f
//double:d
//long double:ld
//ָ��(pointer):p
//����(reference):r
//��һ���д
//ѭ���仯�� i j k

int g_iHeroHp;

void main()
{
	const int c_iHeroMp=100;
	int* pHeroHp = &g_iHeroHp;
	system("pause");
}