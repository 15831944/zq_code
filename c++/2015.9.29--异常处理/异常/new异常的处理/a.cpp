#include <iostream>

//��Щ����������Ϊ�˱�����ĳ����ڴ�ľ���������һ��ʼ
//�ȷ���һЩ�ڴ棬�������ڴ�ľ���ʱ���������ͷ�һЩ
//�ڴ�

#define _MEM_NUM 10

void my_main()
{
	//...
}

void main()
{
	//��ǰ������40MB�ڴ��Ա���������ڴ�漱��ʱ��ʹ��
	void* p[_MEM_NUM];
	for (int i = 0; i < _MEM_NUM; ++i)
		p[i] = malloc(1024 * 1024 * 4);

	int index = 0;
	while (index < 10)
	{
		try
		{
			my_main();
		}
		catch (std::bad_alloc)
		{
			//������std::bad_alloc������ǰ�ڴ���
			//����ϣ���������ͷ�4MB�ڴ�
			free(p[index++]);
		}
	}

	system("pause");
}