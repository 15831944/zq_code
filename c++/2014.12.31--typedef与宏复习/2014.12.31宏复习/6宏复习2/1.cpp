#include<iostream>

//#ifdef ,#ifndef, #else,#endif,#if,#elif

#define ABC//�����û���滻�ı�
#define XYZ 5

void main()
{
#ifdef ABC //�������ABC�꣬�ͱ�������Ĵ���ֱ��#endifΪֹ

	std::cout<<1<<std::endl;

#endif

	//����Ĵ�ӡ�����Ȼ������ִ�У�����һ���ᱻ����
	//�������������û�ж���ABC�꣬���൱��û��
	//std::cout<<1<<std::endl;
	if(0)
		std::cout<<2<<std::endl;

#ifdef DEF //���������DEF�꣬�ͱ����������ֱ��#else
	std::cout<<3<<std::endl;
#else//���û�ж���DEF�꣬�ͱ����������ֱ��#endif
	std::cout<<4<<std::endl;
#endif

#ifndef DEF //���û�ж���DEF�꣬�ͱ����������ֱ��#else
	std::cout<<5<<std::endl;
#else//���������DEF�꣬�ͱ����������ֱ��#endif
	std::cout<<6<<std::endl;
#endif

#if 1 //���#if����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#endif
	std::cout<<7<<std::endl;
#endif

#if 0 //���#if����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#else
	std::cout<<8<<std::endl;
#else//���#if����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�٣��ͱ�������Ĵ���ֱ��#endif
	std::cout<<9<<std::endl;
#endif

#if XYZ == 0//���#if����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#elif
	std::cout<<10<<std::endl;
#elif XYZ == 1//���#elif����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#elif
	std::cout<<11<<std::endl;
#elif XYZ == 2//���#elif����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#else
	std::cout<<12<<std::endl;
#else//���#else����ĳ������ʽ(�������߼�,��ϵ�����)Ϊ�棬�ͱ�������Ĵ���ֱ��#endif
	std::cout<<13<<std::endl;
#endif

	system("pause");
}