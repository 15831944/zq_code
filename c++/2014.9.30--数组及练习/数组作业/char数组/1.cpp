#include <iostream>
using namespace std;
void main()
{
	

	int m=0,n=0;
	int i;	
	char a[10];
	for(i=0;i<10;i++)
	{
		cout<<"�����������"<<i<<"��Ԫ�أ�"<<endl;
		cin>>a[i];
	}
   for(i=0;i<10;i++)
   {
	   if((int)a[i]>=48&&(int)a[i]<=57)
	   {
		   n++;
	   }
	   if( ((int)a[i]>=65&&(int)a[i]<90)|| ((int)a[i]>=97&&(int)a[i]<=122))
	   {
		   m++;
	   }
   }
   cout<<"������ĸ������Ϊ��"<<m<<"��"<<endl;
   cout<<"���������ֵ�����Ϊ��"<<n<<"��"<<endl;

	 
	

	system("pause");
}