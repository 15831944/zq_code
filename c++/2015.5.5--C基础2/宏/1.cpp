#include <stdio.h>
#include <windows.h>
#include <iostream>

//#include����<>��""����
//#define�������
//#undef��ȡ����
//#ifdef��#ifndef��#endif��#else��#if��#elif����������
//#error�����뱨��
//#���ַ�������
//#@���ַ�����
//##���ı�����

#if WINVER < 0x0501
#error ������֧��Windows��Ͱ汾��Ϊ0x0501
#endif

#define _A1(s) #s
#define _A2(s) #@s
#define _A3(s,t) s##t

void main()
{
	char* p = _A1(123abc���);
	//char* p = "123abc���";
	
	char q = _A2(X);
	//char q = 'X';

	int _A3(abc,def) = 1;
	//int abcdef = 1;

	_A3(dou,ble) tt = 1.0;
	//double tt = 1.0;

	//�������ṩ�����ǵ����õĺ���
	std::cout<<__FILE__<<std::endl; //�ļ�·��
	std::cout<<__LINE__<<std::endl; //�к�
	std::cout<<__DATE__<<std::endl; //����
	std::cout<<__TIME__<<std::endl; //ʱ��
	//�����C++�������������Զ�����һ����__cplusplus������������Ĵ���
	//ȷ���ǲ���C++�������ڱ��뱾�ļ�
#ifdef __cplusplus
	std::cout<<"C++"<<std::endl;
#else
	std::cout<<"C"<<std::endl;
#endif

	system("pause");
}