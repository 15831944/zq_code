#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayer
{
public:

	//����һ����������ĳ���
	static cocos2d::CCScene* scene();

	//����create�����ĺ�
	CREATE_FUNC(HelloWorld);
	//static HelloWorld* create()
	//{
	//	HelloWorld *pRet = new HelloWorld();
	//	if (pRet && pRet->init())
	//	{
	//		pRet->autorelease();
	//		return pRet;
	//	}
	//	else
	//	{
	//		delete pRet;
	//		pRet = NULL;
	//		return NULL;
	//	}
	//}

	//��ʼ��
	virtual bool init();

	//�������������ĵ��ù�ϵ
	//scene()
	//{
	//	create()
	//	{
	//		init();
	//	}
	//}

	//�˵���Ӧ����
	void menuCloseCallback(CCObject* pSender);
};

#endif