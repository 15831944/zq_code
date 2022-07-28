#include <iostream>
#include <windows.h>
#include <conio.h>

////��ǰ������ʾ
//int cur_scene = 0;
//
////���õ�ǰ������ʾ
//void set_cur_scene(int index)
//{
//	cur_scene = index;
//}

void set_cur_scene(int index);

//����ĳ�������
void scene1()
{
	std::cout<<"����1"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(1);
}
void scene2()
{
	std::cout<<"����2"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(2);
}
void scene3()
{
	std::cout<<"����3"<<std::endl;
	if (GetAsyncKeyState(VK_SPACE) & 1)
		set_cur_scene(0);
}

//void main()
//{
//	//���ó�ʼ����Ϊ1�ų���
//	set_cur_scene(1);
//	while (1)
//	{
//		system("cls");
//		switch (cur_scene)
//		{
//		case 1: scene1(); break;
//		case 2: scene2(); break;
//		case 3: scene3(); break;
//		//�����Ҫ����µĳ������ͱ���������ط����������������
//		//case 4:	...
//		//case 5:	...
//		}
//		Sleep(33);
//	}
//
//	system("pause");
//}

//װ�س��������ĺ���ָ������
void (* all_scene[8])() = {};

//����ָ������ĳ���
int scene_length = 0;

//��ǰ���������±�
int cur_scene = -1;

//���������������������װ�س�����Ҳ����˵��
//������������ͳһ�Ĺ�������Ӧ�������Ӧ��
//������
bool add_scene(void (* scene)())
{
	if (scene_length == 8)
		return false;
	else
	{
		all_scene[scene_length++] = scene;
		return true;
	}
}

//���õ�ǰ�����±�
void set_cur_scene(int index)
{
	cur_scene = index;
}

void main()
{
	add_scene(scene1);
	add_scene(scene2);
	add_scene(scene3);

	//���ó�ʼ����Ϊ0�ų���
	set_cur_scene(0);

	while (1)
	{
		//�����ж��ٳ�������ѭ�����������޸�
		system("cls");
		if (cur_scene != -1)
			(*all_scene[cur_scene])();
		Sleep(33);
	}

	system("pause");
}