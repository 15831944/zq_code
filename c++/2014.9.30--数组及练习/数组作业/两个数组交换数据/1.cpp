#include <iostream>
using namespace std;
void main()
{
	 int a[5];
	 int b[5];
	 int i,j,t;
	 for(i=0;i<5;i++)
	 {
		 cout<<"�������һ������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>a[i];
	 }
	 for(i=0;i<5;i++)
	 {
		 cout<<"������ڶ�������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>b[i];
	 }
	
	 cout<<"������������ݼ������н������������������"<<endl;
	 system("pause");
	 for(i=0;i<5;i++)
	 {
		 t=a[i];
		 a[i]=b[i];
		 b[i]=t;
	 }
	 cout<<"�������һ�������Ԫ��Ϊ��"<<endl;
	 for(i=0;i<5;i++)
	 {
		 cout<<a[i]<<" ";
	 }
	 cout<<endl;

	 cout<<"������ڶ��������Ԫ��Ϊ��"<<endl;
	  for(i=0;i<5;i++)
	 {
		 cout<<b[i]<<" ";
	 }
	  cout<<endl;

	


	system("pause");
}