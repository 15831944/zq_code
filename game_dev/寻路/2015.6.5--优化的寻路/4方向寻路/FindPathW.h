#ifndef _FIND_PATH_W_H_
#define _FIND_PATH_W_H_

#include <vector>

//��ͼ��char����
//�ϰ���С�ڵ���0�ĵ�ͼ��
//ͨ·������0�ĵ�ͼ��

//�������Ѱ·���ص�
//1���ҵ��������·��
//2��Ч�ʲ���

bool FindPathW(const char* map, //��ͼ
			   int width, //��ͼ��
			   int height, //��ͼ��
			   int start, //��ʼ��
			   int end, //��ֹ��
			   std::vector<int>* path); //�õ���·

#endif