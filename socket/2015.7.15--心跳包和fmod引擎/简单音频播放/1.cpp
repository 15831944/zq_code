#include <iostream>
#include <windows.h>
#include <conio.h>
#pragma comment(lib, "Winmm.lib")

void main()
{
	//ͬ�����������ŵ��������������������أ�
	//Beep(1000, 500);

	PlaySoundA(
		"LoopyMusic.wav",
		0,
		SND_FILENAME | SND_LOOP | SND_ASYNC);
	//SND_FILENAME����ʾ��һ���������ļ���
	//SND_LOOP��ѭ������
	//SND_SYNC��ͬ������
	//SND_ASYNC���첽����

	std::cout<<"�밴������������ţ�";
	_getch();
	PlaySoundA(0, 0, 0);

	system("pause");
}