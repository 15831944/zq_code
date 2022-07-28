#include "MJ.h"


int HuPai(_MJ* p,int n)
{
	//�����ж�
	if(n < 1 || n > 14 || n % 3 != 2)
		return -3;
	//���齫����ת��Ϊchar����
	char pai[27] = {};
	for(int i = 0; i < n;++i)
		pai[(p[i].ds - 1) + (p[i].hs - 1) * 9] += 1;

	//ÿ���Ƶ��������
	for(int  i = 0; i < 27;++i)
	{
		if(pai[i] > 4)
			return -2;
	}
	//��ȱ
	int tong = 0,tiao = 0, wan = 0;
	for(int i = 0; i < 9;++i)
	{
		if(pai[i]>0)
			tong = 1;
	}
	for(int i = 9; i < 18;++i)
	{
		if(pai[i]>0)
			tiao = 1;
	}
	for(int i = 18; i < 27;++i)
	{
		if(pai[i]>0)
			wan = 1;
	}
	if(tong + tiao + wan == 3)
		return -1;
	//�߶Ժ���
	int dui = 0;
	for(int i = 0; i < 27;++i)
	{
		if(pai[i] == 2)
			dui += 1;
		else if(pai[i] == 4)
			dui += 2;
	}
	if(dui == 7)
		return 2;
	//����
	bool jd = false;
	return _HuPai(pai,&jd);
}

int _HuPai(char* pai,bool* jd)
{
	//���û�����˾ͺ�����
	int num = 0;
	for(int i = 0;i < 27;++i)
		num+=pai[i];
	if(num == 0)
		return 1;

	//�ҵ��ʼ���Ƶĵط�
	int begin = 0;
	for(;pai[begin] == 0;++begin)
		;
	//�����ж�
	if(pai[begin] >= 3)
	{
		//ȥ������
		pai[begin] -= 3;
		int r = _HuPai(pai,jd);
		if(1 == r)
			return 1;
		else
		{
			//������ȥ��ɿ��Ӳ��ɹ��Ļ��ͻָ�
			pai[begin] += 3;
		}
	}
	//�����ж�
	if(pai[begin] >= 2 && *jd == false)
	{
		//ȥ������
		pai[begin] -= 2;
		*jd = true;
		int r = _HuPai(pai,jd);
		if(1 == r)
			return 1;
		else
		{
			//������ȥ��ɽ��Բ��ɹ��Ļ��ͻָ�
			pai[begin] += 2;
			*jd = false;
		}
	}
	if((begin % 9 ) < 7 
		&& pai[begin] >= 1
		&& pai[begin + 1] >= 1
		&& pai[begin + 2] >= 1)
	{
		//ȥ��˳��
		pai[begin] -= 1;
		pai[begin + 1] -= 1;
		pai[begin + 2] -= 1;
		//�ڽ�ʣ�µ��Ƽ����ж�
		int r = _HuPai(pai,jd);
		if(r == 1)
			return 1;
		else
		{
			pai[begin] += 1;
			pai[begin + 1] += 1;
			pai[begin + 2] += 1;
		}
	}
	return 0;
}