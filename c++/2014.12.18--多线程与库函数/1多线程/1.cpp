#include<iostream>
#include<windows.h>
#include<conio.h>
#include<process.h>


//�����ĵ��÷�ʽ��Ϊ3�֣�
//������Ҫ������ջ��˳��˭����ջ.
//01)_cdecl:��������������ջ,��������ջ
//02)_stdcall����������������ջ������������ջ
//03)_fastcall:ǰ������С С�ڵ���4byte�Ĳ���������ecx,edx�Ĵ���
//������������������ջ������������ջ
unsigned int _stdcall music(void*)
{
	while(1)
	{
		Beep(200,300);
		Beep(300,300);
		Beep(400,300);
		Beep(500,300);
		Beep(600,300);
		Beep(700,300);
	}
}

void main()
{
	//��music����������һ��ִ������(�߳�)��ִ�У�
	//�������ִ��ʱͬʱ
	_beginthreadex(0,0,music,0,0,0);
	int x = 0,y = 0;
	while(1)
	{
		system("cls");
		for(int i = 0; i < 100; ++i)
		{
			std::cout<<((i == x + y * 10)?"��":"��");
			if(i % 10 == 9)
				std::cout<<std::endl;
		}

		int input = _getch();
		if((input == 'W'||input == 'w') && y > 0)
			y--;
		if((input == 'S'||input == 's') && y < 9)
			y++;
		if((input == 'A'||input == 'a') && x > 0)
			x--;
		if((input == 'D'||input == 'd') && x < 9)
			x++;


	}
	system("pause");
}