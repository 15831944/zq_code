#include <windows.h>
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

void main()
{
	//���ĵ�
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile("hello.xml");

	//�õ�doc������
	TiXmlElement* p = doc->FirstChildElement();
	for (; p; p = p->NextSiblingElement())
	{
		std::cout<<p->Value();

		//�õ��ı�
		if (p->GetText())
			std::cout<<":"<<p->GetText()<<std::endl;
		else
			std::cout<<std::endl;

		TiXmlElement* q = p->FirstChildElement();
		for (; q; q = q->NextSiblingElement())
		{
			std::cout<<q->Value();

			//�õ��ı�
			if (q->GetText())
				std::cout<<":"<<q->GetText()<<std::endl;
			else
				std::cout<<std::endl;

			//�õ�����
			for (TiXmlAttribute* a = q->FirstAttribute(); a; a = a->Next())
			{
				std::cout<<a->Name()<<" = "<<a->Value()<<std::endl;
			}
		}
	}

	//ɾ���ĵ�
	delete doc;

	system("pause");
}

//atoi
//atof