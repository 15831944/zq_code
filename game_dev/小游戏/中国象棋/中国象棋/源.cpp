#include <iostream>
#include "CHESS.h"
#include <conio.h>
#include <Windows.h>
using namespace std;
void main()
{
	//����̨��ɫָ��
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	int GameState=0;
	//x,y--�췽�ƶ�����
	//x1,y1--�����ƶ�����
	int x=0,x1=0,y=QP_H-1,y1=0;
	//b_x,b_y--��¼ѡ�е���������
	//e_x,e_y--��¼���ӽ�Ҫ�ƶ����յ�����
	int b_x,b_y,e_x,e_y;
	//ѡ�����ӵı�־
	bool begin=false;
	//��¼ѡ�е�����
	int value;
	//��¼�췽�ϴ����ӵ�����
	int h_pos;
	//��¼�����ϴ����ӵ�����
	int l_pos;
	cout<<"������ʼ�й����壬";
	system("pause");
	while(1)
	{
		system("cls");
		if(GameState ==0)
		{
			InitQp();
			GameState=1;
			l_pos=x1+y1*QP_W;
			h_pos=x+y*QP_W;
		}
		else
		{
			//�õ���ɫ
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<"-------�й�����--------"<<endl;
			cout<<"-------����˵��-------"<<endl;
			cout<<"�췽����--W:��   A:��   S:��   D:�� "<<endl;
			cout<<"�̷�����--I:��   J:��   K:��   L:�� "<<endl;
			cout<<"Space��ѡ������  N:�˳�"<<endl<<endl;
			int *p=GetQp();
			int pos=(qz==_HF?h_pos:l_pos);
			for(int i=0;i<QP_S;++i)
			{
				if(i==pos)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					cout<<"��";
				}
				else
				{
					//�õ�������ɫ����Ƶ�ͼ
					if(p[i]>0)
						SetConsoleTextAttribute(h,FOREGROUND_GREEN);
					else if(p[i]<0)
						SetConsoleTextAttribute(h,FOREGROUND_RED);
					else
						SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					switch (p[i])
					{
					case 0:cout<<"��";break;
					case _XZ:cout<<"��";break;
					case L_JIANG:cout<<"��";break;
					case H_SHUAI:cout<<"˧";break;
					case L_JU:cout<<"��";break;
					case L_MA:cout<<"��";break;
					case L_PAO:cout<<"��";break;
					case L_SHI:cout<<"��";break;
					case L_XIANG:cout<<"��";break;
					case L_BING:cout<<"��";break;
					case H_JU:cout<<"��";break;
					case H_MA:cout<<"��";break;
					case H_PAO:cout<<"��";break;
					case H_SHI:cout<<"��";break;
					case H_XIANG:cout<<"��";break;
					case H_BING:cout<<"��";break;
					}
				}
				if(i%QP_W == QP_W-1)
					cout<<endl;
			}
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<endl<<"��ǰ���֣�";
			if(qz==_LF)
					SetConsoleTextAttribute(h,FOREGROUND_GREEN);
			else 
					SetConsoleTextAttribute(h,FOREGROUND_RED);
			cout<<(qz==_HF?"�췽":"�̷�")<<endl;
			char input=_getch();
			if((input == 'N' || input =='n') && y>0)
			{
				cout<<"ȷ��Ҫ�˳���Ϸ��,�˳���y��Y��������Ϸ�밴�����"<<endl;
				char sel=_getch();
				if(sel=='Y' || sel=='y')
					break;
				else
					continue;
			}
			//�췽����
			if(qz==_HF)
			{
				if((input == 'W' || input =='w') && y>0)
					y--;
				if((input == 'S' || input =='s') && y<QP_H-1)
					y++;
				if((input == 'A' || input =='a') && x>0)
					x--;
				if((input == 'D' || input =='d') && x<QP_W-1)
					x++;
				h_pos=x+y*QP_W;
			}
			//��������
			else
			{
				if((input == 'I' || input =='i') && y1>0)
					y1--;
				if((input == 'K' || input =='k') && y1<QP_H-1)
					y1++;
				if((input == 'J' || input =='j') && x1>0)
					x1--;
				if((input == 'L' || input =='l') && x1<QP_W-1)
					x1++;
				l_pos=x1+y1*QP_W;
			}
			if(input == ' ')
			{
				//ѡ������
				if(!begin  && ((qz==_HF &&qp[x+y*QP_W]<0) ||(qz==_LF &&qp[x1+y1*QP_W]>0)))
				{
					if(qz==_HF)
					{
						b_x=x;
						b_y=y;
					}
					else
					{
						b_x=x1;
						b_y=y1;
					}
					//��¼����
					begin=true;
					value=qp[b_x+b_y*QP_W];
					//��ǰ���ӱ�Ϊѡ��״̬
					qp[b_x+b_y*QP_W]=_XZ;
					continue;
				}
				//û���ƶ��ղ�ѡ�е����ӣ�������ѡ�����������
				else if(begin && ((qz==_HF &&qp[x+y*QP_W]<0) ||(qz==_LF &&qp[x1+y1*QP_W]>0)) )
				{
					//��ԭ�ϸ�����
					qp[b_x+b_y*QP_W]=value;
					if(qz==_HF)
					{
						b_x=x;
						b_y=y;
					}
					else
					{
						b_x=x1;
						b_y=y1;
					}
					//��¼����ѡ�е�����
					value=qp[b_x+b_y*QP_W];
					qp[b_x+b_y*QP_W]=_XZ;
					continue;
				}
				//ѡ�����Ӻ�Ҫ�ƶ���λ���ж�
				//�ƶ�����Ҫ���Ե��Է����ӣ�Ҫ���ƶ���û�����ӵĵط�
				else if(begin && ((qz==_HF &&qp[x+y*QP_W]>=0) ||(qz==_LF &&qp[x1+y1*QP_W]<=0)) )
				{
					if(qz==_HF)
					{
						e_x=x;
						e_y=y;
					}
					else
					{
						e_x=x1;
						e_y=y1;
					}
					//�õ����̸�Ԫ�ص����ӹ��������������ж�
					//ѡ�����ӵ��ƶ����Ӷ��ɹ����ֽ����´�ѡ���ӵ��жϣ�begin��Ϊfalse
					if(value ==L_JU ||value==H_JU)	
					{
						if(ju(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_PAO ||value==H_PAO)	
					{
						if(pao(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_MA ||value==H_MA)	
					{
						if(ma(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_SHI ||value==H_SHI)	
					{
						if(shi(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_XIANG ||value==H_XIANG)	
					{
						if(xiang(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_JIANG ||value==H_SHUAI)	
					{
						if(wang(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_BING ||value==H_BING)	
					{
						if(bing(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(qp[b_x+QP_W*b_y]==0)
						qz=(qz==_HF?_LF:_HF);
				}
				//ʤ���ж�
				int n_JIANG=0;
				int n_SHUAI=0;
				for(int i=0;i<QP_S;++i)
				{
					if(qp[i]==L_JIANG)
						n_JIANG++;
					if(qp[i]==H_SHUAI)
						n_SHUAI++;
				}
				if(n_JIANG==0)
				{
					cout<<"�췽ʤ��!";
					cout<<"�˳���Ϸ�밴y��Y��"<<endl;
					char sel=_getch();
					if(sel=='Y' || sel=='y')
						break;
				}
				if(n_SHUAI==0)
				{
					cout<<"����ʤ��!";
					cout<<"�˳���Ϸ�밴y��Y��"<<endl;
					char sel=_getch();
					if(sel=='Y' || sel=='y')
						break;
				}
			}
		}
	}
	system("pause");
}