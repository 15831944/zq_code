#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 int sum =0;
	 for(i=0;i<10;i++)
	 {
		 cout<<"����������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>a[i];
	 }
	/* for(j=0;j<10;j++)
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
	 }*/
	for(i=0;i<10;i++)
	{
		sum+=a[i];
	}
	cout<<"ʮ�����ĺ�Ϊ��"<<sum<<endl;



	system("pause");
}