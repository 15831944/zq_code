#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector2.h"

//1�����Դ����е�����
//2�������ͼ��ѧ

class CMatrix3
{
public:
	float
		_11, _21, _31,
		_12, _22, _32,
		_13, _23, _33;

	CMatrix3()
	{
		Identity();
	}

	//��λ��
	void Identity()
	{
		_21 = _31 = _12 = _32 = _13 = _23 = 0.0f;
		_11 = _22 = _33 = 1.0f;
	}

	//����
	void Scaling(float x, float y)
	{
		_11 = x;	_21 = 0.0f;	_31 = 0.0f;
		_12 = 0.0f;	_22 = y;	_32 = 0.0f;
		_13 = 0.0f;	_23 = 0.0f;	_33 = 1.0f;
	}

	//��ת
	void Rotate(float a)
	{
		_11 = cos(a);	_21 = sin(a);	_31 = 0.0f;
		_12 = -_21;		_22 = _11;		_32 = 0.0f;
		_13 = 0.0f;		_23 = 0.0f;		_33 = 1.0f;
	}

	//ƽ��
	void Translate(float x, float y)
	{
		_11 = 1.0f;	_21 = 0.0f;	_31 = 0.0f;
		_12 = 0.0f;	_22 = 1.0f;	_32 = 0.0f;
		_13 = x;	_23 = y;	_33 = 1.0f;
	}
};

//����v ���� ����m = ����output
inline CVector2* _Vec_X_Mat(const CVector2* v,
							const CMatrix3* m,
							CVector2* output)
{
	//����v����ά
	float f1[] = {v->x, v->y, 1.0f};

	//�õ��˷����
	float f2[]
	=
	{
		f1[0] * m->_11 + f1[1] * m->_12 + f1[2] * m->_13,
		f1[0] * m->_21 + f1[1] * m->_22 + f1[2] * m->_23,
		f1[0] * m->_31 + f1[1] * m->_32 + f1[2] * m->_33,
	};

	output->x = f2[0] / f2[2];
	output->y = f2[1] / f2[2];

	return output;
}

#endif