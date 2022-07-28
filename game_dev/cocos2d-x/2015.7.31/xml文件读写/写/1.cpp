#include <windows.h>
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

//1��XML�ļ��ĸ��ڵ����ĵ����������ļ���Ϊһ�����ĸ����
//2���ı���һ������Ľڵ㣬һ����˵һ���ڵ�Ҫ���������ı���
//   ��ô����ڵ��ֻӦ��������ļ��ڵ㲻Ӧ���������ӽڵ�
//3��ÿ���ڵ�������Դ�����������ԣ����Ծ��Ǽ�ֵ��

void main()
{
	//�½��ĵ�
	TiXmlDocument* doc = new TiXmlDocument();

	//Ԫ��
	TiXmlElement* e0 = new TiXmlElement("MMM");
	doc->LinkEndChild(e0);

	TiXmlElement* e1 = new TiXmlElement("abc");
	doc->LinkEndChild(e1);

	TiXmlElement* e2 = new TiXmlElement("def");
	e1->LinkEndChild(e2);

	TiXmlElement* e3 = new TiXmlElement("xyz");
	e1->LinkEndChild(e3);

	//�ı�
	TiXmlText* t1 = new TiXmlText("ABCDEF");
	e2->LinkEndChild(t1);

	TiXmlText* t2 = new TiXmlText("123456");
	e3->LinkEndChild(t2);

	TiXmlText* t3 = new TiXmlText("���");
	e0->LinkEndChild(t3);

	//����
	e2->SetAttribute("����", "21");
	e3->SetAttribute("ѧ��", "123");
	e3->SetAttribute("����", "jack");

	//�����ĵ�
	doc->SaveFile("hello.xml");

	//ɾ���ĵ�
	delete doc;

	system("pause");
}