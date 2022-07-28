#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

#include <cmath>
#include <cassert>

//��������ò�Ҫֱ����0.0ȥ�жϣ�����ȡһ�����������ж�
#define _IS_ZERO(num) ((num)>-0.0001f&&(num)<+0.0001f)

class CVector2
{
public:

	float x, y;

	CVector2(float X = 0.0f, float Y = 0.0f)
		:
	x(X), y(Y)
	{}

	void Set(float X = 0.0f, float Y = 0.0f)
	{
		x = X;
		y = Y;
	}

	//�õ���������
	float Length() const //��Ա�����������const��ʾ�ó�Ա��������ȥ�Գ�Ա��������д����
	{
		return sqrt(x * x + y * y);
	}

	//�õ���λ����
	CVector2 Normalize() const
	{
		//�õ���������
		float length = sqrt(x * x + y * y);

		//���Գ��ȷ���
		assert(!_IS_ZERO(length));

		return CVector2(x / length, y / length);
	}

	//�ӷ�
	CVector2 operator + (const CVector2& that)
	{
		return CVector2(x + that.x, y + that.y);
	}

	//�Լӷ�
	CVector2& operator += (const CVector2& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	//ȡ��
	CVector2 operator - ()
	{
		return CVector2(-x, -y);
	}

	//����
	CVector2 operator - (const CVector2& that)
	{
		return CVector2(x - that.x, y - that.y);
	}

	//�Լ���
	CVector2& operator -= (const CVector2& that)
	{
		x -= that.x;
		y -= that.y;
		return *this;
	}

	//���ˣ����� * ������
	CVector2 operator * (float num)
	{
		return CVector2(x * num, y * num);
	}

	//��ˣ����� * ������
	float operator * (const CVector2& that)
	{
		return x * that.x + y * that.y;
	}

	//ͶӰ
	CVector2 Shadow(const CVector2& that)
	{
		//�õ�that���ȵ�ƽ��
		float f1 = that.x * that.x + that.y * that.y;

		//����that���ȵ�ƽ������
		assert(!_IS_ZERO(f1));

		//�õ�this ��� that�Ľ��
		float f2 = x * that.x + y * that.y;

		//�õ���ֵ
		float f3 = f2 / f1;

		return CVector2(that.x * f3, that.y * f3);
	}

	CVector2 Clock()
	{
		return CVector2(-y, x);
	}

	CVector2 CounterClock()
	{
		return CVector2(y, -x);
	}
};

//���������A��������д����������أ���ô����������
//ֻ�����Ǹ���Ķ������Ҫʹ��ĳ�������֧�������
//�����Ҳ࣬��ôֻ������ȫ�ֵ���������������е������
//��ȫ�������û��this���䱾�ʾ���һ��ȫ�ֺ�������Ϊд
//��hͷ�ļ��еģ����Լ���inline�����������������ش�
//���֧����num * v

//���ˣ����� * ������
inline CVector2 operator * (float num, const CVector2& v)
{
	return CVector2(v.x * num, v.y * num);
}

#endif