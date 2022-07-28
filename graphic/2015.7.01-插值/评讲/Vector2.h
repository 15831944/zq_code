#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

#include <cmath>
#include <cassert>

#define _IS_ZERO(num) ((num)>=-0.0001&&(num)<=0.0001)

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

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	CVector2 Normalize() const
	{
		//�õ�����
		float len = sqrt(x * x + y * y);

		//���Գ��Ȳ�Ϊ0
		assert(!_IS_ZERO(len));

		//���ص�λ����
		return CVector2(x / len, y / len);
	}

	CVector2 operator + (const CVector2& that) const
	{
		return CVector2(x + that.x, y + that.y);
	}

	CVector2& operator += (const CVector2& that)
	{
		x += that.x;
		y += that.y;
		return *this;
	}

	CVector2 operator - () const
	{
		return CVector2(-x, -y);
	}

	CVector2 operator - (const CVector2& that) const
	{
		return CVector2(x - that.x, y - that.y);
	}

	CVector2& operator -= (const CVector2& that)
	{
		x -= that.x;
		y -= that.y;
		return *this;
	}

	CVector2 operator * (float num) const
	{
		return CVector2(x * num, y * num);
	}

	CVector2& operator *= (float num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	//���
	float operator * (const CVector2& that) const
	{
		return x * that.x + y * that.y;
	}

	//ͶӰ
	CVector2 Projection(const CVector2& that) const
	{
		//�õ�that���ȵ�ƽ��
		float len_power2 = that.x * that.x + that.y * that.y;

		//����that���ȵ�ƽ����Ϊ0
		assert(!_IS_ZERO(len_power2));

		//�õ���˽��
		float dot_result = x * that.x + y * that.y;

		//�õ���ֵ
		float f = dot_result / len_power2;

		return CVector2(that.x * f, that.y * f);
	}
};

//���Ҫʹ�ñ���*����Ҳ��������ô����д��
//�������У������������е���������أ���ô
//����Ĭ��ָ��this�����������࣬��������
//ֻ��ȥ����ȫ�ֵĳ˷�
inline CVector2 operator * (float num, const CVector2 v)
{
	return CVector2(v.x * num, v.y * num);
}

#endif