#include <iostream>
#include <cmath>
using namespace std;
void main()
{
	 int a,b=0,n=0,t;
	 cout<<"������һ������������"<<endl;
	 cin>>a;
	 while(a>0)
	 {
		 t=a%10;
		 a=a/10;
		 b=b+(t*pow(2.0,n));
		 n++;
	 }
		 cout<<"ʮ����Ϊ��"<<b<<endl;

		 



	system("pause");
}