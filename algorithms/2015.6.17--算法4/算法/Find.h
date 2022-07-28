#ifndef _FIND_H_
#define _FIND_H_

//����ҵ��˾ͷ����ҵ������ݵ��±꣬�Ҳ����ͷ���b-1
template <typename T>
int find_half(const T* p, //�����ҵ�����
			  int b, //��ʼλ��
			  int e, //��ֹλ��
			  T data, //Ҫ���ҵ�����
			  bool increase = true) //�������з�ʽ��Ϊ���ʾ�������У�Ϊ�ٱ�ʾ��������
{
	int r = b - 1;
	if (increase)
	{
		while (b <= e)
		{
			int h = (b + e) / 2;
			if (data < p[h])
				e = h - 1;
			else if (p[h] < data)
				b = h + 1;
			else
				return h;
		}
	}
	else
	{
		while (b <= e)
		{
			int h = (b + e) / 2;
			if (data < p[h])
				b = h + 1;
			else if (p[h] < data)
				e = h - 1;
			else
				return h;
		}
	}
	return r;
}

//˳�򼯺�
//˳��ӳ��
//��ϣ��
//������
//AVL��
//�����
//�����6�����ݽṹ��Ҫ�������ǲ���

inline const char* FindStrInStr(const char* s1, const char* s2)
{
	int len1 = 0, len2 = 0;
	for (; s1[len1]; ++len1)
		;
	for (; s2[len2]; ++len2)
		;
	int num = len1 - len2 + 1; //�õ��ַ����ܹ��ıȽϴ���
	for (int i = 0; i < num; ++i)
	{
		bool equal = true;
		for (int j = 0; j < len2; ++j)
		{
			if (s1[i + j] != s2[j])
			{
				equal = false;
				break;
			}
		}
		if (equal)
			return s1 + i;
	}
	return 0;
}

#endif