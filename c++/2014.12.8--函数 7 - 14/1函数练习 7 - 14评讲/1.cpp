#include<iostream>

//��������ʽ��������������ʱ��
//��ʽ����������ָ����ߵ�ַ
//����ͨ��ָ������ǵ�ַ����ʽ����
//
//�ں����У�������ר�ŵ������������������
//�����Ͻ�������������������
//
//

//07)�õ�һ������������Ԫ�غ���С��Ԫ�صĺ���(ֻ�õ�һ�ξ͵õ������С)
void GetMaxAndMin(const int* p,//���������
				  int n,//���鳤��
				  int* max,//���ص����ֵ
				  int* min)//���ص���Сֵ
{
	*max = *min = p[0];
	for(int i = 1;i < n;++i)
	{
		if(*min > p[i])
			*min = p[i];
		if(*max < p[i])
			*max = p[i];
	}
}
//08)��һ�������һ�ν��������������ĺ���
void PaiXu(int* p,//���������
		   int begin,//����ʼλ��
		   int end,//�������λ��
		   bool increase)//ѡ���������ǽ���Ϊtrue��������
{
	//1
	//for(int i = begin;i < end;++i)
	//{
	//	for(int  j = 0; j <= end - i - 1;++j)
	//	{
	//		if(increase)
	//		{
	//			if(p[begin + j] > p[begin + j + 1])
	//			{
	//				//����
	//				int temp = p[begin + j];
	//				p[begin + j] = p[begin + j + 1];
	//				p[begin + j + 1] = temp;
	//			}
	//		}
	//		else
	//		{
	//			if(p[begin + j] < p[begin + j + 1])
	//			{
	//				//����
	//				int temp = p[begin + j];
	//				p[begin + j] = p[begin + j + 1];
	//				p[begin + j + 1] = temp;
	//			}
	//		}
	//	}
	//}
	//2
	p += begin;
	int n = end - begin + 1;
	if(increase)
	{
		//ð������
		for(int i = n - 1; i > 0;--i)
		{
			for(int j = 0; j < i;++j)
			{
				if(p[j] > p[j + 1])
				{
					int temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}
			}
		}
	}
	else
	{
		//ѡ������ʽ
		for(int i = 0; i < n - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < n;++k)
			{
				if(p[j] < p[k])
					j = k;
			}
			if(j != i)
			{
				int temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
}

//09)�õ��ַ������ȵĺ���
int GetStringLen(const char* s)//������ַ���
{
	int i = 0;
	for(;s[i];++i)//while(s[i])
		;		  //  ++i;
	return i;
}

//10)���ַ�����������ĺ���
void LiXu1(char* s)
{
	int Len = 0;
	for(;s[Len];++Len)
		;	
	int num = Len / 2;//Len >> 1
	for(int i = 0; i < num;++i)
	{
		char x = s[i];
		s[i] = s[Len - i - 1];
		s[Len - i - 1] = x;
	}
}

char* LiXu2(char* s)
{
	int Len = 0;
	for(;s[Len];++Len)
		;	
	int num = Len / 2;//Len >> 1
	for(int i = 0; i < num;++i)
	{
		char x = s[i];
		s[i] = s[Len - i - 1];
		s[Len - i - 1] = x;
	}
	return s;
}

//11)���ַ������п����ĺ���
char* StringCopy(char* s1,//Ҫ���������ַ���
				 const char* s2)//���������ַ���
{
	for(int i = 0;s1[i] = s2[i];++i)
		;
	return s1;
}

//12)���ַ����������ӵĺ���
char* StringLinJie(char* s1,const char* s2)
{
	char* q = s1;
	for(;*q;++q)
		;
	for(int i = 0; q[i] = s2[i];++i)
		;
	return s1;
}

//13)���ַ������бȽϵĺ���
int StringBijiao(const char* s1,const char* s2)
{
	int i = 0;
	while(s1[i]||s2[i])
	{
		if(s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;
		else 
			++i;
	}
	return 0;
}

//14)���ַ����г��ֵĴ�д��ĸСд������Сд��ĸ��д���ĺ���
char* ChangeChar(char* s,bool dbx)
{
	for(int i = 0;s[i];++i)
	{
		if(dbx && (s[i] >= 'A'&&s[i]<= 'Z'))
			s[i] += 32;
		else if(!dbx && (s[i] >= 'a'&&s[i]<= 'z'))
			s[i] -= 32;
	}
	return s;
}

//15)���������ַ������ݵĺ���

void main()
{
	int a[5] = {2,4,1,6,8};
	int max,min;
	GetMaxAndMin(a,5,&max,&min);
	char s[256] = "123456";
	//LiXu2("abcdef");
	//char* s = "123dg";
	//sָ����ǳ����ڴ����ĵ�ַ
	//"abcdef"�ǳ����ڴ����ĵ�ַ��
	//���ܽ���д����
	char* s1 = LiXu2(s);
	char s2[256] = "asssss";
	char* s3 = StringCopy(s,s2);

	//char s4[] = "1234ddd";
	//char s5[] = "sss";
	//StringCopy(s5,s4);//s5����ֻ��4�ֽ�.s4��8�ֽڣ��������Խ��.
	
	char s4[256] = "1234ddd";
	char s5[] = "sss";
	StringLinJie(s4,s5);
	//�ַ�������ʱ��Ŀ���ַ���������鳤��
	//������ڻ��ߴ���Դ�ַ���(�ַ�����)����ռ�ֽ���
	//��Ŀ���ַ��������ռ�ֽ����ڼ�1.

	StringBijiao("sds","sdsfsdfsd");

	ChangeChar(s4,false);
	system("pause");
}