#include <iostream>
using namespace std;
void main()
{
	 int a[100];
	 int i,j=0,t;
	 cout<<"������һ��ʮ��������"<<endl;
	 cin>>i;

	 while(i!=0)
	 {
		 a[j]=i%2;
		 i=i/2;
		 j++;

	 }
	 cout<<"�����Ķ�����Ϊ��"<<endl;
	 while(i>0){
	 cout<<a[j-1];
	 j--;
	 }
 /*for(i=j-1;i>=0;i--)
	 {
	 cout<<a[i]<<" ";
	 }*/
cout<<endl;
/*while()
{
	a[j]=i%8;
	i=i/8;
	j++;*/

	system("pause");
}