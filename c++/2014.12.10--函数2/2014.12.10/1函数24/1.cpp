#include<iostream>
//24)�õ�ָ��λ�ĺ���
	//bool GetBit(void* p, int n);
	//��p��ʼ�ĵ�ַ�ϵĵ�n��λ��1�ͷ�����,��0�ͷ��ؼ�
bool GetBit(const void* p, int n)
{
	char* q = (char*)p + n / 8;
	return (*q & (1 << (7 - n % 8))) != 0;
}
void main()
{
	
	system("pause");
}