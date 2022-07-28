#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

//���Ǵ洢�������п��ܳ��ִ洢���еġ���Ƭ������ν����Ƭ��
//ָ���Ƿ���ģ�С��Ĵ洢��Ԫ����Щ�洢��Ԫһ�࣬��ô��
//���²���ϵͳҪϣ���������ڴ��Ҫ���кܶ�Ĵ�������
//Ҳ����ʹ�������ϵͳЧ�ʱ���������ڳ����п��ٵġ�������
//���䣨malloc��new��new []�����ͷŶ��ڴ棨free��delete��
//delete []���ͻ�����ڴ���Ƭ���ö���֮��ʹ��ϵͳ���������
//��һ�������˼·����ǰԤ��һ���ϴ���ڴ�飬Ҫʹ�õ�ʱ��
//������ڴ����ȡһ���ȥʹ�ã�Ҫ���յ�ʱ���ٽ��ڴ�黹ԭ
//���ɣ�������ʵ�־����ڴ��

class CMemoryPool
{
	struct NODE
	{
		NODE* pre; //ǰ��ָ��
		NODE* next; //����ָ��
		int use; //ʹ�ñ�־
		int size; //�ڴ���С
	};
	NODE* m_First; //�׽ڵ�

public:

	CMemoryPool(int Size = 1024 * 1024 * 4);
	~CMemoryPool();

	void* Allocate(int Size);
	void Free(void* Mem);
};

#endif