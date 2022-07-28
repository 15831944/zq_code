#ifndef _RENDER_H_
#define _RENDER_H_

class CRender
{
	int m_iW;
	int m_iH;
	char* m_pMap;
public:
	CRender(); 
	~CRender();

	//������Ⱦ��
	void DestroyRender();
	//void RelaseRender

	//������Ⱦ��
	void CreateRender(int w,int h); 

	//�����Ⱦ��
	void ClearRender();

	//������Ⱦ��-�л��ؿ������е�ͼ�����ı�ʱ����
	bool SetRender(int x,int y,const char* c);

	//������Ⱦ�����ⲿ���Ե��ã���Ҫ���ڴ�ӡ
	char* GetRender();
};

#endif