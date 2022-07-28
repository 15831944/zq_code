#include <iostream>
#include <windows.h>
#include "fmod.h"
#pragma comment(lib, "fmodvc.lib")

//��Ƶ����ܶ࣬��������Fmod��Bass��OpenAL�ȣ���Щ
//�����������ǿ�ƽ̨�ĸ������棬��Ƶ�����ִ洢����
//����Ҫ�������������Ĳɼ��ģ�ͬһ��ʱ����ڲɼ���
//��������Խ�࣬��ô�����Ƶ��Խ�ӽ���ʵ����������
//��������Խ��ʧ��Ҳ��Խ��

//���ֲ��ţ�ͬһʱ��ֻ�ܲ���һ����FMOD�����ֲ�������ʽ
//          ���ţ�Ҳ����˵�������Ƶ�ļ������ڴ棬����
//          ÿ��Ҫ���ŵ�ʱ�򣬾�ȥ�򿪵��Ǹ��ļ��ж�ȡ
//          һ��Ҫ���ŵ����ݣ��������ֵĲ���ÿ��ֻ�ܴ�
//          ��һ��
//��Ч���ţ�ͬһʱ����Բ��Ŷ������FSOUND_Init�ڶ�����
//          ����������FMOD����Ч����Ҫ���ļ������뵽�ڴ�
//          �еģ��������ţ�������ͬʱ���Ŷ��

void main()
{
	//��ʼ��
	//1����Ƶ���ż���
	//2�������������
	//3����־
	FSOUND_Init(44100, 16, 0);

	//����Ƶ��
	FSOUND_STREAM* stream = FSOUND_Stream_Open(
		"LoopyMusic.wav",
		FSOUND_LOOP_NORMAL,
		0,
		0);
	
	//������Ƶ��������ֵ�õ����ű���Ƶ���������±�
	int sd = FSOUND_Stream_Play(FSOUND_FREE, stream);

	//�õ�ָ������������
	int v = FSOUND_GetVolume(sd);

	//������Ƶ����
	FSOUND_SAMPLE* sample1 = FSOUND_Sample_Load(FSOUND_FREE, "Windows XP ��̾��.wav", FSOUND_LOOP_OFF, 0, 0);
	FSOUND_SAMPLE* sample2 = FSOUND_Sample_Load(FSOUND_FREE, "Windows XP Ĭ��ֵ.wav", FSOUND_LOOP_OFF, 0, 0);

	while (1)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			v += 10;
			FSOUND_SetVolume(sd, v);
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			v -= 10;
			FSOUND_SetVolume(sd, v);
		}
		if (GetAsyncKeyState(VK_RETURN) & 1)
		{
			FSOUND_Stream_Stop(stream);
		}

		if (GetAsyncKeyState(VK_F1) & 1)
			FSOUND_PlaySound(FSOUND_FREE, sample1);
		if (GetAsyncKeyState(VK_F2) & 1)
			FSOUND_PlaySound(FSOUND_FREE, sample2);

		Sleep(33);
	}

	//ж����Ƶ����
	FSOUND_Sample_Free(sample1);
	FSOUND_Sample_Free(sample2);
	
	//�ر���Ƶ��
	FSOUND_Stream_Close(stream);

	//�ر�
	FSOUND_Close();

	system("pause");
}