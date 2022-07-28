#ifndef _READFILE_H_
#define _READFILE_H_

class CReadFile
{
	 int m_Size;//�ļ���С
	 int m_Pos;//��ȡλ��
	 char* m_Data;//����
public:
	bool Open(const char* filename);
	void Close();
	bool Read_Char(char* data);
	bool Read_Short(short* data);
	bool Read_String(char* data);
	bool Read_Memory(void* data,int count);
};

#endif