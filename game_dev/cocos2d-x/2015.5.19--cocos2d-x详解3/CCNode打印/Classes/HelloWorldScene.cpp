#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
	//����ĳ���ָ��
	CCScene* scene = NULL;
	do 
	{
		//��������
		scene = CCScene::create();
		CC_BREAK_IF(!scene); //if(!scene) break;

		//��������
		HelloWorld* layer = HelloWorld::create();
		CC_BREAK_IF(!layer); //if(!layer) break;

		//���������װ����ղŴ����ĳ���������
		//�����������Ϊ�ղŴ����ĳ����������
		//�ڵ�
		scene->addChild(layer);

		//scene->setPosition(ccp(0, 160));

		//ʵ��һ���򵥵ķ�֧������Ŀ���������
		//��������û���κ�������ô�˴ε�do-while
		//�Ͳ����κ����ã�����������δ�������һ
		//�δ����Ķ���Ϊ0����ô����Ĳ�����������
		//������ȥ�ˣ���Ϊֱ�ӻᱻbreak����do-while
	} while (0);

	//���س���
	return scene;
}

bool HelloWorld::init()
{
	//ʵ�ֱ����е�Ԫ�صĳ�ʼ��
	bool bRet = false;

	do 
	{
		//���ø����init
		CC_BREAK_IF(!CCLayer::init());

		//�����Ͳ������Ĭ������
		//λ�ã�0��0��
		//�ߴ磨���ڿ����ڸߣ�
		//ê�㣨0��0��

		//���������Ĭ������
		//λ�ã�0��0��
		//�ߴ磨ͼ���ͼ���
		//ê�㣨0.5��0.5��

		CCSprite* s1 = CCSprite::create("1.PNG");
		s1->ignoreAnchorPointForPosition(true); //s1����ê���൱������ê��Ϊ��0,0��

		CCSprite* s2 = CCSprite::create("2.PNG");
		s2->setPosition(ccp(100, 50));
		s2->setAnchorPoint(ccp(0.5f, 0.0f));

		CCSprite* s3 = CCSprite::create("3.PNG");
		s3->setPosition(ccp(50, 100));
		s3->setAnchorPoint(ccp(0.5f, 0.5f));

		CCSprite* s4 = CCSprite::create("4.PNG");
		s4->setPosition(ccp(100, 200));
		s4->setAnchorPoint(ccp(0.0f, 0.5f));

		addChild(s1);
		s1->addChild(s2);
		s2->addChild(s3);
		s2->addChild(s4);

		//this->setPosition(ccp(240, 0));

		//���÷���ֵ
		bRet = true;

	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//������Ϸ
	CCDirector::sharedDirector()->end();
}

