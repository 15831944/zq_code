#ifndef _WRITEFILE_H_
#define _WRITEFILE_H_

class CMap;

//�ļ�д�롣��Ҫ���ڴ浵
class CWriteFile
{
public:
	//�����ļ�
	void SaveFile(const char* filename,CMap* map);
};

#endif