#include<iostream>
#include <math.h>
#include <time.h>
#include "1.h"

float TriangleArea(float x,float y,float x1,float y1,float x2,float y2)
{
	//����ľ��룬���ߵľ���֮��С�ڵ����߾Ͳ��ܹ���������
	if(sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y)) <= sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y)))
		return 0.0f;
	//���
	
 //   float k;
	//float d;
	//float h;
	//k=(y1-y)/(x1-x);//б��->0ֵ���
	//d=y1-k*x1;//�ؾ�
	//h=��k*x2+y2+d)*(k*x2+y2+d)/(k*k+1);//��
	//float di=sqrt(pow(abs(x1-x),2)+pow(abs(y1-y),2));//�ױ߳���
	//return sqrt(h)/2*di;

	//�����߱߳�
	float a = sqrt(pow((x-x1),2)+pow((y-y1),2));
	float b = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
	float c = sqrt(pow((x-x2),2)+pow((y-y2),2));
	//�õ��ܳ�һ��
	float z = (a+b+c)/2;
	//�õ����->���׹�ʽ
	return sqrt(z * (z - a) * ( z - c) * ( z - b));
}

int InitRandom()
{
	if(rand() % 2)
		return rand();
	else
		return rand() % rand();
}

int RandomShort(int max,int min)
{
	return rand() % (max - min + 1) + min; 
}

float RandomShort(float max,float min)
{
	return (max - min) * (rand() / 32767.0f) + min;
}

void ArrayRandom(int* MyArray,int begin,int end)
{
	int n  =  end - begin;
	if(n <= 0)
		return;
	if(begin < 0)
		return;
	if(end > 19)
		return;

	for(int i = 0; i < n;++i)
	{
		int j = rand()% (n - i) + begin;
		int a = MyArray[j];
		MyArray[j] = MyArray[end - i];
		MyArray[end - i] = a;
	}
}

void ChineseTime(char* MyArray)
{
	MyArray[0] = 0;
	time_t t = time(0);
	char et[32];
	ctime_s(et,32,&t);
	char nian[4];
	
	memcpy(nian,et + 20,4);
	const char* c_num[]
	=
	{
		"��","һ","��","��","��",
		"��","��","��","��","��"
	};
	for(int i = 0; i < 4;++i)
		strcat(et,c_num[nian[i] - '0']);
	strcat(et,"��");
	
	const char* e_month[]
	=
	{
		"Jan","Feb","Mar","Apr","May","Jun",
		"Jul","Aug","Sep","Oct","Nov","Dec"
	};

	const char* c_month[]
	=
	{
		"һ��","����","����","����","����","����",
		"����","����","����","ʮ��","ʮһ��","ʮ����"
	};
	char yue[4] = {};
	memcpy(yue,et+4,3);
	for(int i = 0; i < 12;++i)
	{
		if(strcmp(yue,e_month[i]) == 0)
		{
			strcat(et,c_month[i]);
			break;
		}
	}

}
void main()
{
	srand((unsigned int)time(0));
	//float a = TriangleArea(1.0f,1.0f,2.0f,2.0f,3.0f,3.0f);
	for(int i = 0; i < 10; ++i)
	{
		std::cout<<RandomShort(10.9f,2.2f)<<std::endl;
	}
	char nyr[32];
	time_t t = time(0);
	char et[32];
	ctime_s(et,32,&t);
	std::cout<<et<<std::endl;
	//ChineseTime(nyr);
	system("pause");
}