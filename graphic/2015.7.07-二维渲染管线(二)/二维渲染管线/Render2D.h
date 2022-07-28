#ifndef _RENDER_2D_H_
#define _RENDER_2D_H_

#include "Matrix3.h"
#include <vector>
#include <windows.h>

#define _WORLD_MATRIX 0 //����任����
#define _CAMERA_MATRIX 1 //������任����
#define _VIEW_MATRIX 2 //�ӿڱ任����

//�õ�������任����
void GetCameraMatrix(CMatrix3* m,
					 const CVector2* eye, //�������λ��
					 const CVector2* at); //���������ȥ��һ����

//�õ��ӿڱ任����
void GetViewMatrix(CMatrix3* m,
				   int s_width, //Դ��
				   int s_height, //Դ��
				   int d_left, //Ŀ���ӿھ������Ͻ�x
				   int d_top, //Ŀ���ӿھ������Ͻ�y
				   int d_width, //Ŀ���ӿھ��ο�
				   int d_height); //Ŀ���ӿھ��θ�

void SetView(int d_left,
			 int d_top,
			 int d_width,
			 int d_height);

//����ָ���任����
void SetMatrix(int type, const CMatrix3* m);

typedef struct _MODAL_2D
{
	std::vector<CVector2> v_coordinate; //��������
	std::vector<CVector2> t_coordinate; //��������
}MODAL2D;
bool LoadMODAL2D(MODAL2D* modal2d, const char* file);
//(x1,y1,u1,v1)
//(x2,y2,u2,v2)
//(x3,y3,u3,v3)
//...
//(xn,yn,un,vn)
//1���������������3��������
//2��uv�����ñ�������ǣ�0.0f~0.999f��

void DrawMODAL2D(HDC destdc, MODAL2D* modal2d, HDC texture);

#endif