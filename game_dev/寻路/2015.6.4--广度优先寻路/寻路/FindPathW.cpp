#include "FindPathW.h"

bool FindPathW(const char* map,
			   int width,
			   int height,
			   int start,
			   int end,
			   std::vector<int>* path)
{
	//�����ж�
	if (!map ||
		width < 1 ||
		height < 1 ||
		start < 0 ||
		start >= width * height ||
		end < 0 ||
		end >= width * height ||
		!path)
		return false;

	//���·��
	path->clear();

	//�����ʼ�������ֹ��
	if (start == end)
	{
		path->push_back(start);
		return true;
	}

	//������
	//�����h1��h2����Ϊ��̬ʹ����
	//���캯��ֻ�������ִ��һ�Σ�
	//���û�б�Ҫִ�У�����������
	//�ռ���
	static std::vector<int> h1, h2;
	h1.clear();
	h2.clear();

	//��ʼ�����
	h1.push_back(start);
	h2.push_back(-1);

	//�õ���ɢ����ʼ����ֹ�±�
	int i1 = 0, i2 = 0;

	//���÷���ƫ����
	static const int offsetx[] = {0,0,-1,1};
	static const int offsety[] = {-1,1,0,0};

	//��·ѭ��
	while (1)
	{
		//��¼��ɢǰ�ĸ�����
		unsigned int i3 = (unsigned int)h1.size();

		//��ɢ��·
		for (int i = i1; i <= i2; ++i)
		{
			//�õ���ǰ��ɢ�������
			int cx = h1[i] % width;
			int cy = h1[i] / width;

			for (int j = 0; j < 4; ++j)
			{
				//�õ���ǰ��ɢ���4�����������
				int dx = cx + offsetx[j];
				int dy = cy + offsety[j];

				//����Խ��
				if (dx >= 0 && dx < width && dy >= 0 && dy < height)
				{
					//�õ���ǰ����ĵ���±�
					int di = dx + dy * width;

					//�ҵ���ֹ����
					if (di == end)
					{
						//װ����ֹ��
						h1.push_back(di);
						h2.push_back(i);

						//�õ�·��
						int cur = (int)h1.size() - 1;
						while (cur != -1)
						{
							path->push_back(h1[cur]);
							cur = h2[cur];
						}

						//ע��·���Ƿ��ŷŵ�
						//end��...��start

						return true;
					}
					//������ֹ��
					else
					{
						//�������ϰ�
						if (map[di] > 0)
						{
							//û���߹�
							bool go = false;
							for (unsigned int k = 0; k < h1.size(); ++k)
							{
								if (di == h1[k])
								{
									go = true;
									break;
								}
							}
							if (!go)
							{
								//����ǰ�㼰�丸�ڵ���Ϣ���븨������
								h1.push_back(di);
								h2.push_back(i);
							}
						}
					}
				}
			}
		}

		//�����з�ɢ�����µ��±�
		if (h1.size() > i3)
		{
			i1 = i3;
			i2 = (int)h1.size() - 1;
		}
		//����û�з�ɢ�����µ���
		//�����ζ��������ͼ����
		//�ĵط��������˻�û����
		//����ֹ��
		else
			break;
	}

	return false;
}