//---------------------------
//���ļ�Ϊ�ļ���ȡ�࣬��Ҫ�����ȡ
//��ͼ�ļ��浵�ļ�
//---------------------------

#ifndef _READFILE_H_
#define _READFILE_H_

class CMap;

class CReadFile
{
public:
	//��ȡ�ܵ�ͼ���ú����ڴ򿪿�ִ���ļ���ʱ���Ӧ�õ���
	void ReadSMap(const char* fileName,CMap* map);

	//��ȡ�浵
	void ReadSave(const char* fileName,CMap* map);
};

#endif