#include "ReadFile.h"
#include <iostream>
#include "Map.h"

//��ȡ�ܵ�ͼ���ú����ڴ򿪿�ִ���ļ���ʱ���Ӧ�õ���
void CReadFile::ReadSMap(const char* fileName,CMap* map)
{
	FILE* pf = 0;
	fopen_s(&pf,fileName,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	int fileLength = ftell(pf);
	rewind(pf);
	
	char* fileBuf = new char[fileLength];
	char* fileBuf1 = fileBuf;
	fread(fileBuf1,1,fileLength,pf);

	int sum = *((int*)fileBuf1);
	fileBuf1 += 4;
	int w = *((int*)fileBuf1);
	fileBuf1 += 4;
	int h = *((int*)fileBuf1);
	fileBuf1 += 4;
	
	map->InitMap(sum,fileLength - 12,fileBuf1,w,h);

	fclose(pf);

	delete []fileBuf;
}

//��ȡ�浵
void CReadFile::ReadSave(const char* fileName,CMap* map)
{
	FILE* pf = 0;
	fopen_s(&pf,fileName,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	int fileLength = ftell(pf);
	rewind(pf);
	
	char* fileBuf = new char[fileLength];
	char* fileBuf1 = fileBuf;
	fread(fileBuf1,1,fileLength,pf);

	int dqgq = *((int*)fileBuf1);
	fileBuf1 += 4;
	
	map->LoadMap(dqgq,fileBuf1);

	fclose(pf);

	delete []fileBuf;
}