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

	 cout<<"�������ʮ��Ԫ�ص����Ϊ��"<<endl;
	
	  for(i=0;i<10;i++)
	 {
		 cout<<"��"<<i<<"һ��Ԫ��Ϊ"<<a[9-i]<<endl;
			
	 }

	 


	system("pause");
}