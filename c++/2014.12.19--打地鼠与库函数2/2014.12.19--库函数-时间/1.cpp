#include<iostream>
#include<time.h>


void main()
{
	//�ַ������ȣ�����������
	//size_t strlen(const char* str);

	//�ַ�������
	//char* strcpy(char* strDestination ,const char* strSource);
	
	//�ַ�������
	//errno_t strcat_s(char* strDestination,
	//	             size_t sizelnBytes,
	//				 const char* strSource);

	//�ַ����Ƚ�
	//int strcmp(const char* string1,const char* string2);
	
	//�����ַ����ַ����е�һ�γ��ֵĵ�ַ
	//char* strchr(const char* str,int c);

	//�����ַ�������һ���ַ����е�һ�γ��ֵĵ�ַ
	//char* strstr(const char* str,const char* strSearch);
	
	//���ַ���ת��Ϊ����
	//int atoi(const char* str);

	//������ת��Ϊ�ַ���
	//errno_t _itoa_s(int value,
	//				char* buffer,
	//				size_t sizelnCharacters,
	//				int radix);

	//��ʽ���ַ�������ӡ
	//printf: %d,%f,%c,%s,%p

	//��ʽ���ַ����������ַ�����
	//int sprintf_s(char* buffer,
	//	          size_t sizeOfBuffer,
	//			  const char* format,
	//			  ....);//����

	//ʱ�亯��
	//time_t ���ʾ���һ��__int64��__int64��΢��Ϊ
	//C++�����8�ֽڴ�����
	
	//01)�õ���������ʱ�䣨�룩
	//time_t time(time_t* timer);

	//time_t t1 = time(0);
	//time_t t2;
	//time(&t2);


	//02)��ָ���ĸ�������ʱ��ת��Ϊ��׼������ʱ���ַ���
	//errno_t ctime_s(char* buffer,//�洢����ʱ���ַ������ַ������׵�ַ
	//	            size_t sizelnBytes,//�洢����ʱ���ַ������ַ����鳤��
	//				const time_t* time);//��������ʱ��

	//char t[32];
	//ctime_s(t,32,&t1);
	//std::cout<<t<<std::endl;

	system("pause");
}