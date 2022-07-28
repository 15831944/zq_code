#include "Tree.h"
#include <iostream>
#include <string>

void main()
{
	char fn[256];
	std::cout<<"������Ҫ��ȡ���ļ���";
	std::cin>>fn;

	//��ȡ�ļ�
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"�޷���ָ���ļ���";
		system("pause");
		return;
	}
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = (char*)malloc(fs + 1);
	fread(fd, 1, fs, pf);
	fclose(pf);
	fd[fs] = 0;

	//�����ļ�
	std::string str;
	for (int i = 0; i < fs; ++i)
	{
		if (fd[i] > ' ')
			str += fd[i];
	}
	free(fd);

	//������֯

	//�������ڵ�
	TN* root = createTN(); root->data = fn;

	//���õ�ǰ���ڵ�
	TN* parent = root;

	//"123{abc{}def{xyz{}kkk{1{}2{}3{}}456{}}}"
	//data=123

	std::string data;
	for (int i = 0; i < (int)str.length(); ++i)
	{
		if (str[i] == '{')
		{
			TN* p = createTN();
			p->data = data;
			data.clear();
			insertTN(parent, p);
			parent = p;
		}
		else if (str[i] == '}')
		{
			parent = parent->parent;
		}
		else
			data += str[i];
	}

	preTN(root, 0);

	system("pause");
}