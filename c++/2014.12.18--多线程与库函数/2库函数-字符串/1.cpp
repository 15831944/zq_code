#include<iostream>

//01)�ַ���
//size_t����unsigned int 
//΢����ΪC������һЩ�⺯������ȫ������΢���ṩ
//��һЩ��Щ����������汾����_s��Ϊ���
void main()
{
	//01)
	//����str������ַ����ĳ��ȣ�����������
	//size_t strlen(const char* str);

	//std::cout<<strlen("123abc���")<<std::endl;
	//char* s1 = "xyzdef";
	//std::cout<<strlen(s1)<<std::endl;
	//std::cout<<strlen(s1 + 2)<<std::endl;
	//char s2[] = "9876543210";
	//std::cout<<strlen(&s2[4])<<std::endl;
	//char s3 = 'Z';
	//std::cout<<strlen(&s3)<<std::endl;
	
	//02)
	//��strSource������ַ���������strDestination��
	//ָ����ڴ��У�����������0һ�𿽱�������strDestination
	//char* strcpy(char* strDestination,const char* strSource);

	//char s4[32] = "abcdefghi";
	//strcpy(s4,"xyz");
	//char s5[] = "ABC";
	//strcpy(s5,"XXYYZZ");//s5û���㹻�Ŀռ�����"XXYYZZ"
	//strcpy_s//��ȫ�汾

	//03
	//��strSource������ַ������ӵ�strDestination
	//��������ַ������棬����sizelnBytes������д
	//strDestination��ָ����ڴ��Ͽ��õ��ֽ���
	//errno_t strcat_s(char* strDestination,
	//	             size_t sizelnBytes,
	//				 const char* strSource);

	//char s7[16] = {};
	//strcat_s(s7,16,"abc");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"XYZ");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"QWE");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"0123456789987");//���������ֽ���
	//std::cout<<s7<<std::endl;

	//04)

	//�Ƚ�string1,string2�����ַ���
	//��string1 > string2����1
	//��string1 == string2����0
	//��string1 < string2����-1
	//int strcmp(const char* string1,const char* string2);
	//std::cout<<strcmp("abc","as")<<std::endl;
	//std::cout<<strcmp("abc","abc")<<std::endl;
	//std::cout<<strcmp("abc","ab")<<std::endl;
	
	//05)
	//����c��str�е�һ�γ��ֵĵ�ַ��û�оͷ���0
	//char* strchr(const char* str,int c);
	
	std::cout<<strchr("123abc123abc",'a')<<std::endl;
	std::cout<<strchr("123abc123abc",'c') + 4<<std::endl;
	//���ص�������char*����ôcout�Ͱ��������ַ������׵�ַ
	//��ӡ�ַ���.0x00000000�����ַ�ǲ��ɷ��ʵ�

	//std::cout<<strchr("123abc123abc",'x')<<std::endl;
	//��ȡλ�� 0x00000000 ʱ�������ʳ�ͻ

	//06)
	//����strSearch��str�е�һ�γ��ֵĵ�ַ��û�оͷ���0
	//char* strstr(const char* str,const char* strSearch);
	
	//std::cout<<strstr("123abc123abc","bc12")+4<<std::endl;
	//const char* s8 = strstr("123abc123abc","bc3");
	//std::cout<<s8<<std::endl;
	system("pause");
}