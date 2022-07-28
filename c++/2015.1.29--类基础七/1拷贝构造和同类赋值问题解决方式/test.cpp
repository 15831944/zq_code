#include <iostream>

class �䳤����
{
	int* p;
	int n;
public:
	�䳤����(int num)
	{
		n = num;
		p = new int[n];
	}

	�䳤����(const �䳤����& that)
	{
		n = that.n;
		p = new int[n];
		for(int i = 0; i < n; ++i)
			p[i] = that.p[i];
	}

	�䳤����& operator = (const �䳤����& that)
	{
		if(this != &that)
		{
			delete []p;
			p = new int[n = that.n];
			for(int i = 0; i < n; ++i)
				p[i] = that.p[i];
		}
		return *this;
	}

	~�䳤����()
	{
		delete []p;
	}

	bool ����(int pos,int value)
	{
		if(pos < 0 || pos >= n)
			return false;

		p[pos] = value;
		return true;
	}

	int* ��ȡ(int pos)
	{
		return (pos < 0 || pos >= n) ? 0 : p + pos; 
	}
};

void main()
{
	�䳤���� a(5);
	for(int i = 0; i < 5; ++i)
		a.����(i,i);
	�䳤���� a1 = a;
	for(int i = 0; i < 5; ++i)
		std::cout<<*(a1.��ȡ(i))<<std::endl;
	system("pause");
}