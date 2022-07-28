// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//���ü������Ǻܶ�߼��������������ջ��ƵĻ���

typedef struct _ABC
{
	int num; //�洢�ж��ٸ�ָ��ָ���Լ�
	//...
}* ABC;

ABC createABC()
{
	ABC abc = (ABC)malloc(sizeof(_ABC));
	abc->num = 1; //��ʾ��һ��ָ��ָ���˱�����
	return abc;
}
ABC evaluateABC(ABC abc)
{
	abc->num += 1; //��ʾ����һ��ָ��ָ���˱�����
	return abc;
}
void DestroyABC(ABC abc)
{
	abc->num -= 1;
	if (abc->num == 0) //��ʾû��ָ��ָ�򱾶�����������������
		free(abc);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ABC abc1 = createABC();
	ABC abc2 = evaluateABC(abc1);
	ABC abc3 = evaluateABC(abc1);
	ABC abc4 = evaluateABC(abc1);

	DestroyABC(abc1);
	DestroyABC(abc2);
	DestroyABC(abc3);
	DestroyABC(abc4);

	return 0;
}

