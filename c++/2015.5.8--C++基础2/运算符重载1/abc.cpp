#include <iostream>
#include <assert.h>

//���������
//1��ʹ�����ǵ���֧��ԭ������ʹ�õ������
//2�����ص�������Ĺ�����ȫ�ɳ���Ա����
//3����������صı��ʾ��Ǻ���
//4����������һ�������ʹ����������أ����ܻ������������
//5���ַ������е�+��һЩ��ѧ���е����㣬��Щ���Ͽ��������������

class Cfraction //����
{
	int m_Numerator;
	int m_Denominator;

	int _max_common_divisor(int n1, int n2)
	{
		int n3 = n1 < n2 ? n1 : n2;
		for (int i = n3; i > 1; --i)
		{
			if (n1 % i == 0 && n2 % i == 0)
				return i;
		}
		return 1;
	}

public:

	//����
	Cfraction(int n = 1, int d = 1)
		:
	m_Numerator(n),
	m_Denominator(d)
	{
		//���Է�ĸ��Ϊ0
		assert(m_Denominator != 0);

		//Լ��
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;
	}

	//�ӷ�
	Cfraction operator + (const Cfraction& that)
	{
		//��ĸ��ͬ
		if (m_Denominator == that.m_Denominator)
		{
			Cfraction f(m_Numerator + that.m_Numerator, m_Denominator);
			return f;
		}
		//��ĸ����ͬ
		else
		{
			Cfraction f(
				m_Numerator * that.m_Denominator + that.m_Numerator * m_Denominator,
				m_Denominator * that.m_Denominator);
			return f;
		}
	}

	//�Ը�ֵ�ӷ�
	Cfraction& operator += (const Cfraction& that)
	{
		//��ĸ��ͬ
		if (m_Denominator == that.m_Denominator)
			m_Numerator += that.m_Numerator;
		//��ĸ����ͬ
		else
		{
			m_Numerator = m_Numerator * that.m_Denominator + that.m_Numerator * m_Denominator;
			m_Denominator = m_Denominator * that.m_Denominator;
		}
		//Լ��
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;
		return *this;
	}

	Cfraction operator * (const Cfraction& that)
	{
		Cfraction f(
			m_Numerator * that.m_Numerator,
			m_Denominator * that.m_Denominator);
		return f;
	}

	Cfraction& operator *= (const Cfraction& that)
	{
		m_Numerator *= that.m_Numerator;
		m_Denominator *= that.m_Denominator;

		//Լ��
		int cd = _max_common_divisor(m_Numerator, m_Denominator);
		m_Numerator /= cd;
		m_Denominator /= cd;

		return *this;
	}
};

void main()
{
	int a = 1, b = 2;
	(a += b) = 4; //+=�Ľ�������ı���

	Cfraction f1(18, 24);
	Cfraction f2 = f1;
	Cfraction f3 = f1 + f2;
	f3 = f1 * f2;

	system("pause");
}