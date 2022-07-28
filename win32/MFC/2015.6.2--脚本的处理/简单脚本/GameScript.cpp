#include "GameScript.h"
#include <iostream>

bool CGameScript::LoadScript(const char* fn)
{
	//�õ��ű��ı�

	//1���õ��ű���ʼ����
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return false;
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = new char[fs + 1];
	fd[fs] = 0;
	fread(fd, 1, fs, pf);
	fclose(pf);

	//2������ű���ʼ���ݵ��µ��ַ�����
	char* buf = new char[fs + 1];
	int len = 0;
	for (int i = 0; i < fs; ++i)
	{
		//�ɼ��ַ�
		if (fd[i] > ' ')
			buf[len++] = fd[i];
	}
	buf[len] = 0;
	delete [] fd;

	//װ������

	//1���õ����������
	int command_num = 0;
	for (int i = 0; i < len; ++i)
	{
		if (buf[i] == ')')
			command_num += 1;
	}

	//2��ѭ������
	m_Commands.clear();
	char* p = buf;
	char* p0, * p1;
	for (int i = 0; i < command_num; ++i)
	{
		_COMMAND command;

		//�õ�ʱ��
		p0 = strchr(p, '(');
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._time = atoi(p0 + 1);

		//�õ�����
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._type = atoi(p0);

		//�õ��뾶
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._radius = atoi(p0);

		//�õ����
		p0 = p1 + 2;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._x = atoi(p0);
		p0 = p1 + 1;
		p1 = strchr(p0, '>');
		*p1 = 0;
		command._y = atoi(p0);

		//�õ�����
		p0 = p1 + 2;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._dir = atoi(p0);

		//�õ��ٶ�
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._speed = atoi(p0);

		//�õ�����
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._step = atoi(p0);

		//�õ���־
		p0 = p1 + 1;
		p1 = strchr(p0, ')');
		*p1 = 0;
		command._flag = atoi(p0);

		//������ʼ��ַ
		p = p1 + 1;

		//װ�����
		m_Commands.push_back(command);
	}

	//��������
	for (int i = (int)m_Commands.size() - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (m_Commands[j]._time > m_Commands[j + 1]._time)
			{
				_COMMAND c = m_Commands[j];
				m_Commands[j] = m_Commands[j + 1];
				m_Commands[j + 1] = c;
			}
		}
	}

	return true;
}

void CGameScript::ResetTime()
{
	m_Time = 0;
	m_CurCmd = 0;
}

void CGameScript::Run()
{
	//�ƶ�����
	for (std::vector<_OBJECT>::iterator it = m_Objects.begin(); it != m_Objects.end(); )
	{
		//�ƶ�����
		if (it->cur_step == 0)
		{
			if (0 == it->flag)
				it = m_Objects.erase(it);
			else if (1 == it->flag)
				++it;
			else if (2 == it->flag)
			{
				it->cur_step = it->all_step;
				static const int change_dir[] = {4,5,6,7,0,1,2,3};
				it->dir = change_dir[it->dir];
				++it;
			}
		}
		//�����ƶ�
		else
		{
			//701
			//6 2
			//543
			static const int offsetx[] = {0,1,1,1,0,-1,-1,-1};
			static const int offsety[] = {-1,-1,0,1,1,1,0,-1};
			it->x += offsetx[it->dir] * it->speed;
			it->y += offsety[it->dir] * it->speed;
			it->cur_step -= 1;
			++it;
		}
	}

	//��������
	while (m_CurCmd < (int)m_Commands.size() && m_Time == m_Commands[m_CurCmd]._time)
	{
		_OBJECT obj
			=
		{
			m_Commands[m_CurCmd]._type,
			m_Commands[m_CurCmd]._radius,
			m_Commands[m_CurCmd]._x,
			m_Commands[m_CurCmd]._y,
			m_Commands[m_CurCmd]._dir,
			m_Commands[m_CurCmd]._speed,
			m_Commands[m_CurCmd]._step,
			m_Commands[m_CurCmd]._step,
			m_Commands[m_CurCmd]._flag
		};

		//װ�����
		m_Objects.push_back(obj);

		//��ǰ���������������
		m_CurCmd += 1;
	}
	
	//ʱ�����
	m_Time += 1;
}

std::vector<CGameScript::_OBJECT>* CGameScript::GetObjects()
{
	return &m_Objects;
}