#include<iostream>

//02)�ַ������������͵�ת��
void main()
{
	//01)
	//���ַ���ת��Ϊ���������أ�ת�����˾ͷ���0
	//int atoi(const char* str);

	int a1 = atoi("123");
	int a2 = atoi("+123");
	std::cout<<a2<<std::endl;
	int a3 = atoi("-123");
	std::cout<<a3<<std::endl;
	int a4 = atoi("abc");
	std::cout<<a4<<std::endl;

	//02)
	//��valueת��Ϊ�ַ�������ŵ�����Ϊ
	//sizelnCharacters��buffer��ַ�У�radix
	//��ʾ����
	//errno_t_itoa_s(int value,
	//	           char* buffer,
	//			   size_t sizelnCharacters,
	//			   int radix);

	char s1[32];
	_itoa_s(123,s1,32,10);
	std::cout<<s1<<std::endl;

	//printf("hello world\n");
	//printf������:��ʽ���ַ�������ӡ
	//"%d"�ᱻ�����滻
	//"%f"�ᱻ�������滻
	//"%c"�ᱻ�ַ��滻
	//"%s"�ᱻ�ַ����滻
	//"%p"�ᱻ��ַ�滻
	//printf("��Ҫ��ӡ��������%d+%d=%d\n",100,200,300);
	//printf("%d,%f,%c,%s,%p\n",1,3.14,'A',"abc",&a1);

	//03)
	//��ʽ���ַ����������ַ�����
	//int sprintf_s(char* buffer,
	//	          size_t sizeOfBuffer,
	//			  const char* format,
	//			  ....);

	char s2[64];
	sprintf_s(s2,64,"%d��%f��%c��%s��%p\n",1,3.14,'A',"abc",&a1);
	std::cout<<s2<<std::endl;
	system("pause");
}