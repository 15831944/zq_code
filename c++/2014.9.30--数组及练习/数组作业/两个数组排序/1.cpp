#include <iostream>
using namespace std;
void main()
{
	 int a[5];
	 int b[5];
	 int i,j,t,m;
	 bool x;
	 bool y;
	 
	 do
	 {
	 cout<<"���С��������5������"<<endl;
	 for(i=0;i<5;i++)
	 {
		 cout<<"�������һ������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>a[i];
	 }
	 
	 
	 for(i=0;i<4;i++)
	 {
	 if(a[i]>a[i+1])
	 {
	
		 cout<<"���鲻�Ǵ�С��������������"<<endl;
	     x=true;
		 system("pause");
	     system("cls");
		 break;
	 }
	 else
	 {   
		 x=false;
 
	 }
	 }
	 }
	 while(x);
	 
	 
	//-------------------------------
	 
	 
	 do
	 {
	cout<<"���С��������5������"<<endl;
	  for(i=0;i<5;i++)
	 {
		 cout<<"������ڶ�������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>b[i];
	 }


	  for(i=0;i<4;i++)
	 {
	 if(b[i]>b[i+1])
	 {
	
		 cout<<"���鲻�Ǵ�С��������������"<<endl;
	     y=true;
		 system("pause");
	     system("cls");
		 break;
	 }
	 else
	 {   
		 y=false;
 
	 }
	 }
	 }
	 while(y);




	  //-------------------------------
	  cout<<"��������Ĺ�ͬ�����СΪ��"<<endl;

     for(j=0;j<5;j++)
	 {
		 for(i=0;i<5;i++)
		 {
			 if(a[j]>b[i])
			 {
				 t=a[j];
				 a[j]=b[i];
				 b[i]=t;
			 }
		 }
	 }
	 for(m=0;m<4;m++)
	 {
		 for(i=0;i<4-m;i++)
		 {
			 if(b[i]>b[i+1])
			 {
				 t=b[i];
				 b[i]=b[i+1];
				 b[i+1]=t;
			 }
		 }
	 }
	 for(i=0;i<5;i++)
	 {

	 cout<<a[i]<<" ";
	 }
	  for(i=0;i<5;i++)
	 {

	 cout<<b[i]<<" ";
	 }

	system("pause");
}