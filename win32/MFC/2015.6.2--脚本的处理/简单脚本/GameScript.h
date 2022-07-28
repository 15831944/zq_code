//��ν�ű���script����ָ������ʱ���ء����롢ִ�еĳ���һ����˵
//�ű���ר�ŵĽű����ԣ�����JavaScript��Lua��Python�Ƚű���ʹ��
//��Щ�ű��ķ��������ǽ�����ű����ԵĴ���д���ļ��У�Ȼ��������
//��������C��C++��Java����������Щ�ĳ����м��ز��������ǣ�Ȼ
//��ִ�����ǣ�����ǽű��Ĺ������̣���Ϊ�����������˵����Ҫ����
//�����飬���ݵĶ�������ݵĴ����ű�����Ҳ�����⣬Ҳ���Զ����
//�������ݣ��������ݱȽϼ򵥣��������ݷǳ�����Ҫ�õ�����ԭ���֪
//ʶ���������ҽ���һ�¼��ýű������������������ǵ���Ϸ����

#ifndef _GAME_SCRIPT_H_
#define _GAME_SCRIPT_H_

#include <vector>

class CGameScript
{
	//����
	struct _COMMAND
	{
		int _time; //��ʼʱ��
		int _type; //����
		int _radius; //�뾶
		int _x, _y; //���
		int _dir; //����01234567��ʾ��Χ�˸�����
		int _speed; //�ٶ�
		int _step; //����
		int _flag; //��־��0��ʾҪ��ʧ��1��ʾ����ʧ��2��ʾѭ��
	};
	std::vector<_COMMAND> m_Commands;

public:

	//����
	struct _OBJECT
	{
		int type; //����
		int radius; //�뾶
		int x, y; //λ��
		int dir; //����
		int speed; //�ٶ�
		int all_step; //�ܲ���
		int cur_step; //��ǰ����
		int flag; //��־
	};

private:
	std::vector<_OBJECT> m_Objects;

	//ʱ��
	int m_Time;

	//��ǰ������������
	int m_CurCmd;

public:

	//���ؽű�
	bool LoadScript(const char* fn);

	//����ʱ��
	void ResetTime();
	
	//ϵͳ����
	void Run();

	//�õ�����
	std::vector<_OBJECT>* GetObjects();
};

#endif