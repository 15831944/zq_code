#ifndef _WRITEFILE_H_
#define _WRITEFILE_H_

class CWriteFile
{
	char m_FileName[256];
	int m_Size;
	int m_Length;
	char* m_Data;

	//д���⣬����Ϊ���Ǳ�����Ҫ���ڲ����ܣ�������
	//�ⲿʹ��
	void _addmem(int size)
	{
		if(m_Size - m_Length < size)
		{
			m_Size += size;
			m_Size *= 2;
			char* p = new char[m_Size];
			for(int i = 0; i < m_Lenght;++i)
				p[i] = m_Data[i];
			delete []m_Data;
			m_Data = p;
		}
	}
public:
	//CWriteFile();

	void Open(const char* filename);
	void Close();
	void WriteBool(bool data);
	void WriteShort(short data);
	void WriteChar(char data);
	void WriteString(const char* data);
	void WriteMemory(const void* data,int count);
};


#endif