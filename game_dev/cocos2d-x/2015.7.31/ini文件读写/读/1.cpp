#include <windows.h>
#include <iostream>

void main()
{
	//��ȡ�ַ���
	char buf[256];
	GetPrivateProfileStringA(
		"Baseline",
		"Dir",
		"ʧ�ܣ�", //��ȡʧ�ܵ��ַ���
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	GetPrivateProfileStringA(
		"Baseline",
		"Dir2",
		"ʧ�ܣ�", //��ȡʧ�ܵ��ַ���
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	GetPrivateProfileStringA(
		"Baseline",
		"FileName",
		"ʧ�ܣ�", //��ȡʧ�ܵ��ַ���
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	//��ȡ�ڴ�
	char x[32] = {};
	GetPrivateProfileStructA(
		"qwe",
		"a1",
		x,
		6, //ֻ����дini���ֽڵ�����������������У���ֽ�
		".\\xyz.ini");
	
	int y;
	GetPrivateProfileStructA(
		"qwe",
		"a2",
		&y,
		4, //ֻ����дini���ֽڵ�����������������У���ֽ�
		".\\xyz.ini");

	GetPrivateProfileStringA(
		"qwe",
		"a2",
		"ʧ�ܣ�", //��ȡʧ�ܵ��ַ���
		buf,
		256,
		".\\xyz.ini");
	std::cout<<buf<<std::endl;

	system("pause");
}