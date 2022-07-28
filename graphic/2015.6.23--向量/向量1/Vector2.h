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
};

#endif