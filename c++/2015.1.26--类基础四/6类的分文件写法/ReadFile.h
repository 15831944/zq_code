#ifndef _READFILE_H_
#define _READFILE_H_

class CReadFile
{
private:
	int m_Size;//�ļ���С
	int m_Pos;//��ǰ��ȡλ��
	char* m_Data;//����
public:
	CReadFile();
	~CReadFile();
	bool Open(const char* filename);
	//....
};

#endif