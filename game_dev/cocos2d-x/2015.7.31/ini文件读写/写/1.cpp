#include <windows.h>
#include <iostream>

//΢��Ϊ�˷�������д�����ݣ������Ƴ�һ�ײ���ini�ļ�
//�ĺ������������׺������Ժ����׵ض�дini�ļ��е����ݣ�
//ע��ini�ļ��ĸ�ʽ���£�
//FileName.ini
//[AppName1]
//KeyName1=String1
//KeyName2=String2
//...
//KeyName3=String3
//
//[AppName2]
//KeyName1=String1
//KeyName2=String2
//...
//KeyName3=String3

void main()
{
	//д���ַ���
	WritePrivateProfileStringA(
		"ABC", //����
		"a", //��
		"123", //ֵ
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"ABC", //����
		"b", //��
		"456", //ֵ
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"���", //����
		"c", //��
		"����", //ֵ
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"���", //����
		"c", //��
		"hello", //ֵ
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"���", //����
		"c", //��
		"hello", //ֵ
		".\\qwe.ini");

	//д��һ���ڴ棬���д���ʱ�����һ��У���ֽڣ�����ֽ�
	//�����е��ֽڵĺ�
	WritePrivateProfileStructA(
		"OOO",
		"a1",
		"123abc",
		6,
		".\\xyz.ini");
	int x = 0x11223344; //44 33 22 11
	WritePrivateProfileStructA(
		"OOO",
		"a2",
		&x,
		4,
		".\\xyz.ini");

	system("pause");
}