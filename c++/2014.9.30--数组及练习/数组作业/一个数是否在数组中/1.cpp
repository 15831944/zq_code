#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 bool x=true;
	 bool y;
	 do
	 {
	 cout<<"���С������ʮ������"<<endl;
	 for(i=0;i<10;i++)
	 {
		 cout<<"����������ĵ�"<<i<<"��Ԫ�أ���������";
			 cin>>a[i];
	 }
	  for(i=0;i<4;i++)
	 {
	 if(a[i]>a[i+1])
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





	 //----------------
	 cout<<"��������һ��������"<<endl;
	 cin>>j;

	 for(i=0;i<10;i++)
	 {

	 if(j==a[i])
	 {
		 x=false;
		 break;
	 }
	 
	
	 }
	 if(x)
	 {
		 cout<<j<<"û�г�����������"<<endl;
	 }
	 else
	 {
		  cout<<j<<"������������"<<endl;
	 }


	


	system("pause");
}