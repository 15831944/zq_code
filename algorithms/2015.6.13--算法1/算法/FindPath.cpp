#include "FindPath.h"

bool FindPathW(const char* map, //��ͼ�׵�ַ
			   int w, //��ͼ��
			   int h, //��ͼ��
			   int b, //��ʼ���±�
			   int e, //��ֹ���±�
			   std::vector<int>* path) //�õ���·
{
	//�����ж�
	if (!map ||
		w < 1 ||
		h < 1 ||
		b < 0 || b >= w * h ||
		e < 0 || e >= w * h ||
		!path)
		return false;

	//���·
	path->clear();

	//����ʼ�������ֹ��
	if (b == e)
	{
		//װ����ʼ��
		path->push_back(b);
		return true;
	}

	//��������
	std::vector<int> help1, help2;

	//��ʼ��������
	help1.push_back(b);
	help2.push_back(-1);

	//��ʼ��Ҫ��ɢ�ĸ���������1�е��±�
	int i1 = 0, i2 = 0;

	//4�������ƫ����
	int offsetx[] = {0,0,-1,1};
	int offsety[] = {-1,1,0,0};

	//Ѱ·ѭ��
	while (1)
	{
		//��¼��ɢǰ�ĸ������鳤��
		int len = (int)help1.size();

		//��ɢ
		for (int i = i1; i <= i2; ++i)
		{
			//�õ���ǰ���±������
			int ci = help1[i];
			int cx = ci % w;
			int cy = ci / w;
			
			//���ݵ�ǰ�����귢ɢ4�������������±�
			for (int j = 0; j < 4; ++j)
			{
				int dx = cx + offsetx[j];
				int dy = cy + offsety[j];
				int di = dx + dy * w;

				//����Խ��
				if (dx >= 0 && dx < w && dy >= 0 && dy < h)
				{
					//�ҵ���·
					if (di == e)
					{
						//��ԭ·����path

						//����ֹ��������
						help1.push_back(e);
						help2.push_back(i);

						//�õ���ǰӦ�÷���path��·����
						//help1�����е��±�
						int index = (int)help1.size() - 1;

						//��ԭ·��
						while (index != -1)
						{
							path->push_back(help1[index]);
							index = help2[index];
						}

						return true;
					}

					//�������ϰ�
					if (map[di] > 0)
					{
						//û���߹�
						bool go = false;
						for (int k = 0; k < (int)help1.size(); ++k)
						{
							if (di == help1[k])
							{
								go = true;
								break;
							}
						}
						if (!go)
						{
							//���븨������
							help1.push_back(di);
							help2.push_back(i);
						}
					}
				}
			}
		}

		//����û�з�ɢ
		if (len == (int)help1.size())
			break;
		//���η�ɢ��
		else
		{
			//���·�ɢ�ķ�Χ�±�
			i1 = len;
			i2 = (int)help1.size() - 1;
		}
	}

	return false;
}

bool _FindPathD(const char* map,
				int w,
				int h,
				int e,
				std::vector<int>* help,
				std::vector<int>* path)
{
	//�ж��Ƿ�����ֹ�㣬�������ֹ
	//��ͷ������ʾ�ҵ�·��
	if (e == path->back())
		return true;

	//4�������ƫ����
	int offsetx[] = {0,0,-1,1};
	int offsety[] = {-1,1,0,0};

	//�õ���ǰ�������
	int ci = path->back();
	int cx = ci % w;
	int cy = ci / w;

	//��ɢ4���������Ѱ·
	for (int i = 0; i < 4; ++i)
	{
		int dx = cx + offsetx[i];
		int dy = cy + offsety[i];
		int di = dx + dy * w;

		//û��Խ��
		if (dx >= 0 && dx < w && dy >= 0 && dy < h)
		{
			//�����ϰ�
			if (map[di] > 0)
			{
				//û���߹�
				bool go = false;
				for (int j = 0; j < (int)path->size(); ++j)
				{
					if (path->at(j) == di)
					{
						go = true;
						break;
					}
				}
				if (!go)
				{
					for (int j = 0; j < (int)help->size(); ++j)
					{
						if (help->at(j) == di)
						{
							go = true;
							break;
						}
					}
					if (!go)
					{
						//��ǰλ�÷���·����
						path->push_back(di);

						//�ݹ��ж�
						bool r = _FindPathD(map, w, h, e, help, path);

						//�ҵ���·
						if (r)
							return true;
						//�Ҳ���·
						else
						{
							//����λ�÷��븨������
							help->push_back(di);

							//����λ�ô�·����ȥ��
							path->pop_back();
						}
					}
				}
			}
		}
	}

	return false;
}

bool FindPathD(const char* map, //��ͼ�׵�ַ
			   int w, //��ͼ��
			   int h, //��ͼ��
			   int b, //��ʼ���±�
			   int e, //��ֹ���±�
			   std::vector<int>* path) //�õ���·
{
	//�����ж�
	if (!map ||
		w < 1 ||
		h < 1 ||
		b < 0 || b >= w * h ||
		e < 0 || e >= w * h ||
		!path)
		return false;

	//���·
	path->clear();

	//����ʼ�������ֹ��
	if (b == e)
	{
		//װ����ʼ��
		path->push_back(b);
		return true;
	}

	//����ʼ��װ��·��
	path->push_back(b);

	//���ø�������
	std::vector<int> help;

	//�ݹ����Ѱ·
	return _FindPathD(map, w, h, e, &help, path);
}