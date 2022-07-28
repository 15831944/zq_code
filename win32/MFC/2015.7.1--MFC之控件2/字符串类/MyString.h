#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <iostream>
#include <cassert>

class CMyString
{
	int len; //û���������
	char* str;

public:

	//�޲ι���
	CMyString()
	{
		len = 0;
		str = new char[len + 1];
		str[0] = 0;
	}

	//���ι���
	CMyString(const char* s)
	{
		len = (int)strlen(s);
		str = new char[len + 1];
		strcpy_s(str, len + 1, s);
	}

	//��������
	CMyString(const CMyString& that)
	{
		len = that.len;
		str = new char[len + 1];
		strcpy_s(str, len + 1, that.str);
	}

	//����
	~CMyString()
	{
		delete [] str;
	}

	//ͬ�ำֵ
	CMyString& operator = (const CMyString& that)
	{
		if (this != &that)
		{
			delete [] str;
			len = that.len;
			str = new char[len + 1];
			strcpy_s(str, len + 1, that.str);
		}
		return *this;
	}

	//��ֵ
	CMyString& operator = (const char* s)
	{
		delete [] str;
		len = (int)strlen(s);
		str = new char[len + 1];
		strcpy_s(str, len + 1, s);
		return *this;
	}

	//ͬ��ӷ�
	CMyString operator + (const CMyString& that)
	{
		CMyString ms; //�������޲ι���
		delete [] ms.str; //�����ͷ����޲ι����п��ٵĶ��ڴ�
		ms.len = len + that.len;
		ms.str = new char[ms.len + 1];
		strcpy_s(ms.str, ms.len + 1, str);
		strcat_s(ms.str, ms.len + 1, that.str);
		return ms;
	}

	//�ӷ�
	CMyString operator + (const char* s)
	{
		CMyString ms; //�������޲ι���
		delete [] ms.str; //�����ͷ����޲ι����п��ٵĶ��ڴ�
		ms.len = len + (int)strlen(s);
		ms.str = new char[ms.len + 1];
		strcpy_s(ms.str, ms.len + 1, str);
		strcat_s(ms.str, ms.len + 1, s);
		return ms;
	}

	//ͬ���Ը�ֵ�ӷ�
	CMyString& operator += (const CMyString& that)
	{
		int cur_len = len + that.len;
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		strcat_s(cur_str, cur_len + 1, that.str);
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	//ͬ���Ը�ֵ�ӷ�
	CMyString& operator += (const char* s)
	{
		int cur_len = len + (int)strlen(s);
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		strcat_s(cur_str, cur_len + 1, s);
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	//char�Ը�ֵ�ӷ�
	CMyString& operator += (char c)
	{
		int cur_len = len + 1;
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		cur_str[cur_len - 1] = c;
		cur_str[cur_len] = 0;
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	char& operator [] (int index)
	{
		assert(index >= 0 && index < len);
		return str[index];
	}

	const char* GetString()
	{
		return str;
	}

	int GetLength()
	{
		return len;
	}
};

#endif