#include <iostream>
using namespace std;
void main()
{
	int b,i,j=0;
	int a[10];
	for(i=0;i<10;i++)
	{
		cout<<"����������ĵ�"<<i<<"��Ԫ��"<<endl;
		cin>>a[i];
	}
	for(i=0;i<10;i++)
	{
		if((a[i]&(a[i]-1))==0)
		  j++;
	}
	cout<<"������2������"<<j<<"��"<<endl;
	system("pause");
}