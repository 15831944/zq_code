#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 for(i=0;i<10;i++)
	 {
		 cout<<"����������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>a[i];
	 }
	 for(j=0;j<10;j++)
	 {
		 for(i=0;i<9-j;i++)
		 {
			 if(a[i]>a[i+1])
			 {
				 t=a[i];
				 a[i]=a[i+1];
				 a[i+1]=t;
			 }
		 }
	 }
	 cout<<"����������СΪ��"<<endl;
	 for(i=0;i<10;i++)
	 {
		 cout<<a[i]<<" ";
	 }


	system("pause");
}