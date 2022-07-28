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

		//ʵ��һ���򵥵ķ�֧������Ŀ���������
		//��������û���κ�������ô�˴ε�do-while
		//�Ͳ����κ����ã�����������δ�������һ
		//�δ����Ķ���Ϊ0����ô����Ĳ�����������
		//������ȥ�ˣ���Ϊֱ�ӻᱻbreak����do-while
	} while (0);

	//����
	//����
	//  �ǲ˵�
	//  �����˵���ͼ��
	//  �Ǳ�ǩ
	//  ������

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

		//һ�����һ���˵�
		//����һ���˵���ͼ�����
		CCMenuItemImage* pCloseItem = CCMenuItemImage::create(
			"Close/CloseNormal.png", //δ���״̬��ͼ��
			"Close/CloseSelected.png", //�����״̬��ͼ��
			this, //��Ӧ����˵��ĺ��������������
			menu_selector(HelloWorld::menuCloseCallback)); //��Ӧ����˵��ĺ���
		CC_BREAK_IF(!pCloseItem); //if(!pCloseItem) break;

		//���ò˵���ͼ���λ��
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		//����һ���˵�
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);

		//���ò˵�λ��
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pMenu); //if(!pMenu) break;

		//��Ӳ˵�Ϊ������ӽڵ�
		this->addChild(pMenu, 1);

		//�������һ����ǩ

		//����һ����ǩ
		CCLabelTTF* pLabel = CCLabelTTF::create(
			"Hello World", //Ҫ��ʾ���ַ���
			"Arial", //�����������
			24); //���ִ�С
		CC_BREAK_IF(!pLabel); //if(!pLabel) break;

		//�õ����ڳߴ�
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//���ñ�ǩ��λ��
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		//��ӱ�ǩΪ������ӽڵ�
		this->addChild(pLabel, 1);

		//�������һ������

		//����һ������
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(!pSprite); //if(!pSprite) break;

		//���þ���λ��
		pSprite->setPosition(ccp(size.width / 2, size.height / 2));

		//��Ӿ���Ϊ������ӽڵ�
		this->addChild(pSprite, 0);

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

