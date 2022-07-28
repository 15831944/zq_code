//����ͨ������ȫ�ֵ�new��delete��
//new []��delete []��������ﵽ
//�ڴ���ٵ�Ŀ�ģ�ͨ������Ĵ���
//���ǿ��Խӹ�ԭʼ�Ķ��ڴ������
//һ����˵���ǿ���ͨ������Ĵ���
//����¼���ڴ�ķ��䡢�ͷ������
//���Ҫ�����malloc��free����ô
//ֻ���á����ӡ����������

#include <iostream>

int new_num = 0;
int delete_num = 0;

void* operator new (size_t size)
{
	void* mem = malloc(size);

	//��¼������Ϣ
	char buf[256];
	sprintf_s(buf, 256, "������%d���ֽ��ڵ�ַ%p,��ǰ����%d�ͷ�%d\r\n", size, mem, ++new_num, delete_num);
	FILE* pf = 0;
	fopen_s(&pf, "HeapLog.txt", "a"); //wb�����ԭ�ļ���aֻ�Ǵ򿪲������
	fwrite(buf, strlen(buf), 1, pf);
	fclose(pf);

	return mem;
}

void operator delete (void* mem)
{
	free(mem);

	//��¼�ͷ���Ϣ
	char buf[256];
	sprintf_s(buf, 256, "�ͷ���%p,��ǰ����%d�ͷ�%d\r\n", mem, new_num, ++delete_num);
	FILE* pf = 0;
	fopen_s(&pf, "HeapLog.txt", "a");
	fwrite(buf, strlen(buf), 1, pf);
	fclose(pf);
}

void* operator new [] (size_t size)
{
	return operator new (size);
}

void operator delete [] (void* mem)
{
	operator delete (mem);
}