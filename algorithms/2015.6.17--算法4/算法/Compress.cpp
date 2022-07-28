#include "Compress.h"

struct _TYPE1
{
	unsigned char type : 2, num : 6;
};
struct _TYPE2
{
	unsigned short type : 2, num : 14;
};
struct _TYPE3 //��Ȼ��4�ֽڵ���ֻ��3�ֽ�
{
	unsigned int type : 2, num : 22;
};
struct _TYPE4
{
	unsigned int type : 2, num : 30;
};

void RLE_Compress(const void* p1,
				  int len1,
				  void* p2,
				  int* len2)
{
	//����ѹ��֮������ֽ���
	*len2 = 0;

	//ѭ��ԭʼ����
	const char* q1 = (const char*)p1;
	for (int i = 0; i < len1; ++i)
	{
		//�õ���ǰ�ֽ���ͬ����ʼλ�ú���ֹλ��
		int begin = i, end;
		for (end = i + 1; q1[begin] == q1[end]; ++end)
			;
		
		//�õ���ǰ�ֽڳ��ֵĴ���
		int num = end - begin;

		//����i
		i = end - 1;

		//���������
		if (num == 1)
			*len2 += 1;
		else if (num > 1 && num <= 63)
			*len2 += 3;
		else if (num > 63 && num <= 16383)
			*len2 += 4;
		else if (num > 16383 && num <= 4194303)
			*len2 += 5;
		else
			*len2 += 6;
	}

	//���p2Ϊ0����ô�˴��ͷ���
	if (0 == p2)
		return;

	*len2 = 0;

	//ѹ��
	//ѭ��ԭʼ����
	q1 = (const char*)p1;
	char* q2 = (char*)p2;
	for (int i = 0; i < len1; ++i)
	{
		//�õ���ǰ�ֽ���ͬ����ʼλ�ú���ֹλ��
		int begin = i, end;
		for (end = i + 1; end < len1 && q1[begin] == q1[end]; ++end)
			;
		
		//�õ���ǰ�ֽڳ��ֵĴ���
		int num = end - begin;

		//����i
		i = end - 1;

		//�������ݵ�λ��
		char* r2 = q2 + *len2;

		//���������
		if (num == 1)
		{
			*r2 = q1[begin];
			*len2 += 1;
		}
		else if (num > 1 && num <= 63)
		{
			*r2 = q1[begin];
			*(r2 + 1) = q1[begin];
			_TYPE1* t1 = (_TYPE1*)(r2 + 2);
			t1->type = 0;
			t1->num = num;

			*len2 += 3;
		}
		else if (num > 63 && num <= 16383)
		{
			*r2 = q1[begin];
			*(r2 + 1) = q1[begin];
			_TYPE2* t2 = (_TYPE2*)(r2 + 2);
			t2->type = 1;
			t2->num = num;

			*len2 += 4;
		}
		else if (num > 16383 && num <= 4194303)
		{
			*r2 = q1[begin];
			*(r2 + 1) = q1[begin];
			_TYPE3* t3 = (_TYPE3*)(r2 + 2);
			t3->type = 2;
			t3->num = num;

			*len2 += 5;
		}
		else
		{
			*r2 = q1[begin];
			*(r2 + 1) = q1[begin];
			_TYPE4* t4 = (_TYPE4*)(r2 + 2);
			t4->type = 3;
			t4->num = num;

			*len2 += 6;
		}
	}
}