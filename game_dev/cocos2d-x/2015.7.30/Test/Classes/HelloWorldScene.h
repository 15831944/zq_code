#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	
	//�����Լ���HelloWorld�����ٴ���һ��
	//������Ȼ����Լ�����Ϊ�����������
	//�ڵ㣬Ȼ�󷵻س���
	static cocos2d::Scene* createScene();

	//����ĺ�ᱻ�滻Ϊ����
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

	//��ʼ����װ���˲˵�����ǩ������
	virtual bool init();

	//createScene()
	//{
	//	create()
	//	{
	//		init();
	//	}
	//}

	//�˵���Ӧ������һ�����в˵���ô������Զ����ñ�����
	void menuCloseCallback(cocos2d::Ref* pSender);

	//ͼ��˵���
	MenuItemImage* closeItem, * closeItem2;

	void menuCloseCallback2(cocos2d::Ref* pSender);
	MenuItemImage* kkk;
};

#endif

//Scene����������cocos2d�еĳ������԰����ܶ�Ĳ㣬����
//       �������õ�ǰ���еĳ���
//Layer������㣨����������������Ǽ������еĳ�����
//Size������ߴ磬������Ҫ���ݾ���width��height
//Vec2������������������Ҫ���ݾ���x��y
//MenuItemImage������ͼ��˵���
//Ref�����ü����࣬�������е�cocos2d-x����ĸ��඼����
//Node�����ڵ��࣬�������㡢����ȿ�����֯Ϊ���ͽṹ����ĸ��඼����