#include "LoadStage.h"
#include <iostream>

int LoadStage(const char* BoxStage, LinkList linklist)
{
	//�ͷű���ԭ�е����ݲ����
	for(int i = 1; i <= LengthLinkList(linklist);++i)
		free(GetLinkList(linklist,i)->m);
	ClearLinkList(linklist);

	//�򿪹ؿ��ļ�
	FILE* pFile;
	fopen_s(&pFile,BoxStage,"rb");
	if(!pFile)
		return -3;
	fseek(pFile,0,SEEK_END);
	int iFileSize = ftell(pFile) + 1;
	rewind(pFile);

	//�����ڴ棬���ؿ��ļ���Ϣ�����ڴ���
	char* pFileBuffer = (char*)malloc(sizeof(char) * iFileSize);
	fread(pFileBuffer,sizeof(char),iFileSize - 1,pFile);
	fclose(pFile);
	pFileBuffer[iFileSize - 1] = 0;

	//���س���Ϊ0
	for(int i = 0; i < iFileSize ;++i)
	{
		if(pFileBuffer[i] == 0x0d || pFileBuffer[i] == 0x0a)
			pFileBuffer[i] = 0;
	}

	//���ڴ��е��ļ����ݷֹؿ�������ʱ�ڴ���
	char* pBuffer = (char*)malloc(sizeof(char) * iFileSize);
	char* q = pBuffer;
	int pBufferSize = iFileSize;
	char* p = pFileBuffer;
	int StageNum = 0;
	while(p < pFileBuffer + iFileSize)
	{
		if(*p != 0)
		{
			strcpy_s(q,pBufferSize,p);
			pBufferSize -= (int)strlen(q) + 1;
			p += strlen(p) + 1;
			q += strlen(q) + 1;
			StageNum++;
		}
		else
			++p;
	}
	q = pBuffer;
	free(pFileBuffer);
	if(StageNum < 1)
	{
		free(pBuffer);
		return -2;
	}
	for(int i = 0; i < StageNum;++i)
	{
		fopen_s(&pFile,q,"rb");
		if(!pFile)
		{
			free(pBuffer);
			for(int i = 1; i <= LengthLinkList(linklist);++i)
				free(GetLinkList(linklist,i)->m);
			ClearLinkList(linklist);
			return -1;
		}
		//�ж��Ƿ�Ϊ����Ϸ�ĵ�ͼ�ļ�
		char FileMark[8];
		fread(&FileMark,sizeof(char),8,pFile);
		if(strcmp(FileMark,"PUSHBOX") != 0)
		{
			fclose(pFile);
			free(pBuffer);
			for(int i = 1; i <= LengthLinkList(linklist);++i)
				free(GetLinkList(linklist,i)->m);
			ClearLinkList(linklist);
			return 0;
		}

		_BOX_STAGE bs;
		fread(&bs.w , sizeof(int),1,pFile);
		fread(&bs.h , sizeof(int),1,pFile);
		bs.m = (char*)malloc(sizeof(char)* bs.w * bs.h);
		fread(bs.m,sizeof(char),bs.w * bs.h,pFile);
		
		fclose(pFile);

		for(int i = 0; i < bs.w * bs.h; ++i)
		{
			if(_YX == bs.m[i] || _QIU == bs.m[i])
			{
				bs.x = _XY_X(i,bs.w);
				bs.y = _XY_Y(i,bs.w);
				break;
			}
		}
		
		PushLinkList(linklist,bs);

		q += (int)strlen(q) + 1;
	}
	free(pBuffer);
	return 1;
}