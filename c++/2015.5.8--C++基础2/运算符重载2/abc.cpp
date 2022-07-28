#include <iostream>
#include <assert.h>

class CZuoBiao
{
	int x, y;

public:

	CZuoBiao(int X = 0, int Y = 0)
		:
	x(X),y(Y)
	{}

	//ǰ������
	CZuoBiao& operator ++ ()
	{
		++x;
		++y;
		return *this;
	}

	//����������C++�涨��һ�����õ�int�β���Ϊ��ǰ�õ�����
	CZuoBiao operator ++ (int)
	{
		CZuoBiao zb(x, y);
		x++;
		y++;
		return zb;
	}

	//�±����������
	int& operator [] (bool b)
	{
		return b ? x : y;
	}

	//�±���������أ���Ȼ�﷨���У����������÷�û�б�Ҫ
	int& operator [] (const char* s)
	{
		return strlen(s) > 5 ? x : y;
	}

	//��ʽת��

	//Ϊ���ǵ������һ��Ĭ�Ͽ��Ա�ת��Ϊint����ʽת��
	operator int ()
	{
		return x + y;
	}

	operator const char* ()
	{
		return "Hello World";
	}
};

void main()
{
	int x = 1;
	(++x) = 2; //ǰ������������Ľ���Ǳ���
	//(x++) = 3; //��������������Ľ������ʱ��

	CZuoBiao zb1;
	CZuoBiao zb2 = ++zb1;
	CZuoBiao zb3 = zb1++;

	//�ೣ��
	//д��������();
	//ע�⣺�����ò�ͬ�Ĺ�������ʼ��һ������
	int a = 1; //���� = ����;
	CZuoBiao zb4 = CZuoBiao(5, 5); //���� = ����;
	CZuoBiao zb5 = CZuoBiao(); //���� = ����;
	zb5[true] = 7;
	zb5[false] = 8;
	zb5["sdljfjlksdjflkjsdflkj"] = 9;
	zb5["sdl"] = 10;

	//��������ȥCZuoBiao����ȥ������û�п��Ա�ת��Ϊ
	//int���͵���ʽת�����о͵����Ǹ���ʽת��
	int p = zb5;
	double q = zb5; //zb5���Ա���תΪint����תΪdouble
	const char* r = zb5;
	//int* w = zb5; //�޷�����ת���ı��ʽ���ᱨ��

	system("pause");
}