#include <iostream>
#include"CHESS.h"
int qp[QP_S]=
{
	5,4,3,2,1,2,3,4,5,
	0,0,0,0,0,0,0,0,0,
	0,6,0,0,0,0,0,6,0,
	7,0,7,0,7,0,7,0,7,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	-7,0,-7,0,-7,0,-7,0,-7,
	0,-6,0,0,0,0,0,-6,0,
	0,0,0,0,0,0,0,0,0,
	-5,-4,-3,-2,-1,-2,-3,-4,-5
};
char qz;
//˧�ͽ�
bool wang(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//˧�Ļ��Χ
		if(qz==_HF)
		{
			if(cx>=3 && cx<=5 && cy<QP_H && cy>QP_H-4)
			{
				if(cx==e_x && cy == e_y)
					return true;
			}
		}
		//���Ļ��Χ
		else
		{
			if(cx>=3 && cx<=5 && cy<3 && cy>=0)
			{
				if(cx==e_x && cy == e_y)
					return true;
			}
		}
	}
	return false;
}
//��
bool  shi(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={1,1,-1,-1};
	const int offset_y[]={-1,1,1,-1};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		if(qz==_HF)
		{
			//�˵Ļ��Χ
			if(cx>=3 && cx<=5 && cy<=9 && cy>=7)
			{
				//�˵�ʮ��û������
				if(cx==e_x && cy == e_y && (qp[76]==0||qp[76]==_XZ))
					return true;
			}
		}
		else
		{
			if(cx>=3 && cx<=5 && cy<3 && cy>=0)
			{
				if(cx==e_x && cy == e_y && (qp[14]==0||qp[14]==_XZ))
					return true;
			}
		}
	}
	return false;
}
//��
bool  xiang(int b_x,int b_y,int e_x,int e_y)
{
	//�����ж��Ƿ������м�������
	const int offset_x[]={1,1,-1,-1};
	const int offset_y[]={-1,1,1,-1};
	const int pd_x[]={2,2,-2,-2};
	const int pd_y[]={-2,2,2,-2};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		bool flag=false;
		//�췽��Ļ��Χ
		if(qz==_HF)
		{
			if(cx>=0 && cx<QP_W && cy<QP_H && cy>QP_H-6)
			{
				//�����м�û������
				if(qp[cx+cy*QP_W]==0)
				{
					if(b_x+pd_x[i]==e_x && b_y+pd_y[i] == e_y)
						return true;
				}
			}
		}
		//������
		else
		{
			if(cx>=0 && cx<=QP_W && cy<5 && cy>=0)
			{
				if(cx>=0 && cx<=QP_W && cy<5 && cy>=0)
				{
					if(qp[cx+cy*QP_W]==0)
					{
						if(cx+offset_x[i]==e_x && cy+offset_y[i] == e_y)
							return true;
					}
				}
			}
		}
	}
	return false;
}
//��
bool ju(int b_x,int b_y,int e_x,int e_y)
{
	//�����ĸ�����ƫ����
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		bool flag=false;
		bool flag1=false;
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//��һ�������ϴӿ�ʼ�����ҵ���һ�������ӵĵط�
		for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
		{
			if(qp[cx+QP_W*cy]!=0)
			{
				flag=true;
				flag1=true;
				break;
			}
			else
				flag1=false;
		}
		//�ҵ�������Ӻ󣬱�־���Ļ��Χ
		if(flag)
		{
			for(;cx!=b_x||cy!=b_y;cx-=offset_x[i],cy-=offset_y[i])
			{
				if(cx==e_x && cy==e_y)
				{
					return true;
				}
			}
		}
		//һ��������û�����ӣ���������������������λ���ƶ�
		else if(!flag1)
		{
			for(;cx!=b_x||cy!=b_y;cx-=offset_x[i],cy-=offset_y[i])
			{
				if(cx==e_x && cy==e_y)
				{
					return true;
				}
			}
		}
	}
	return false;
};
//��
bool ma(int b_x,int b_y,int e_x,int e_y)
{
	//��һ��ֱ���Ƿ������ӣ�4�������ƫ����
	const int pd_x[]={0,1,0,-1};
	const int pd_y[]={-1,0,1,0};
	//����յ�8������ƫ����
	const int offset_x[]={-1,1,2,2,1,-1,-2,-2,};
	const int offset_y[]={-2,-2,-1,1,2,2,1,-1,};
	for(int i=0;i<4;++i)
	{
		int px=pd_x[i]+b_x;
		int py=pd_y[i]+b_y;
		//����ֱ��û�����ӣ�����������
		if(IN_QP(px,py) && qp[px+py*QP_W]==0)
		{
			//��������ƫ�����Ĺ�ϵΪ������ϵ
			int j=2*i;
			if( (b_x+offset_x[j]==e_x &&b_y+offset_y[j]==e_y)||
				(b_x+offset_x[j+1]==e_x &&b_y+offset_y[j+1]==e_y) )
				return true;
		}
	}
	return false;
}
//��
bool pao(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		bool flag=false;
		bool flag1=false;
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//�ӿ�ʼ�����ҵ�һ��ֱ�ߵĵ�һ������
		for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
		{
			if(qp[cx+QP_W*cy]!=0)
			{
				flag=true;
				break;
			}
		}
		//���ø����ӣ����ڿ��Խ��гԵ�����
		if(flag)
		{
			cx+=offset_x[i],cy+=offset_y[i];
			for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
			{
				if(qp[cx+QP_W*cy]!=0)
				{
					flag1=true;
					break;
				}
			}
			if(flag1 && cx==e_x && cy==e_y)
			{
				return true;
			}
		}
	}
	//���һ��ֱ��û�����ӣ������������ӹ���һ��
	if(ju( b_x, b_y, e_x, e_y))
		return true;
	return false;
}
//��
bool bing(int b_x,int b_y,int e_x,int e_y)
{
	//�췽������������û���·���
	const int hf_x[]={0,1,-1};
	const int hf_y[]={-1,0,0};
	//����������������û���Ϸ���
	const int lf_x[]={1,0,-1};
	const int lf_y[]={0,1,0};
	//�췽�����Χ
	if(qz==_HF)
	{
		//û�С����ӡ�
		if(b_y<=6 && b_y>=5)
		{
			if(b_x+hf_x[0]==e_x && b_y+hf_y[0]==e_y)
				return true;
		}
		//����
		else
		{
			for(int i=0;i<3;++i)
			{
				int cx=hf_x[i]+b_x;
				int cy=hf_y[i]+b_y;
				if(cx>=0 && cx<QP_W && cy>=0 && cy<=6)
				{
					if(cx==e_x && cy==e_y)
						return true;
				}
			}
		}
	}
	//������
	else
	{
		if(b_y<=4 && b_y>=3)
		{
			if(b_x+lf_x[1]==e_x && b_y+lf_y[1]==e_y)
				return true;
		}
		else
		{
			for(int i=0;i<3;++i)
			{
				int cx=lf_x[i]+b_x;
				int cy=lf_y[i]+b_y;
				if(cx>=0 && cx<QP_W && cy>=3 && cy<QP_H)
				{
					if(cx==e_x && cy==e_y)
						return true;
				}
			}
		}
	}
	return false;
}
//��ʼ������
void InitQp()
{
	int qp[QP_S]=
	{
		5,4,3,2,1,2,3,4,5,
		0,0,0,0,0,0,0,0,0,
		0,6,0,0,0,0,0,6,0,
		7,0,7,0,7,0,7,0,7,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		-7,0,-7,0,-7,0,-7,0,-7,
		0,-6,0,0,0,0,0,-6,0,
		0,0,0,0,0,0,0,0,0,
		-5,-4,-3,-2,-1,-2,-3,-4,-5
	};
	qz=_HF;
}
//�������
int* GetQp()
{
	return qp;
}
