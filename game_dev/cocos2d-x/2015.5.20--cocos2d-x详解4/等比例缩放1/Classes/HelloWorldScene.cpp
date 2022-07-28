#include "HelloWorldScene.h"
#include "AppDelegate.h"

HelloWorld::HelloWorld()
{}

HelloWorld::~HelloWorld()
{}

CCScene* HelloWorld::getScene()
{
	CCScene* scene = CCScene::create();
	scene->addChild(this);
	return scene;
}

void HelloWorld::onEnter()
{
	//���ø����onEnter
	CCLayer::onEnter();

	//���ñ��㿪������
	setTouchEnabled(true);

	//���ñ���Ϊ������Ϣ�ķַ�Ŀ��
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
		this, //����Ϊ�ַ�Ŀ��Ĳ�
		1, //�ַ����ȼ������ȼ�Խ��Խ�ȵõ�������Ϣ
		true); //�������Ϊ�棬��ô����������Ĳ㷢�ʹ�����Ϣ����֮��������

	//��������ĸ���
	scheduleUpdate();
}

void HelloWorld::onExit()
{
	//���ø����onEnter
	CCLayer::onExit();
}

bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{

}

void HelloWorld::draw()
{
	//�����cocos2d�������ƺ������ײ���õ���OpenGL�еĻ�
	//�ƺ�����ֻ����draw���汻���ã������ط�����û��Ч����
	//��Щ�����Ļ��ƺ����У���һ����ǰ��ɫ�ĸ�����ǿ���
	//ͨ����صĺ������õ�ǰ��ɫ�������õ���ɫ����������Щ
	//��ͼ�����Ľ���У���ǰ��ɫĬ���ǰ�ɫ��

	ccColor4B c1 = {0x7f, 0x7f, 0x7f, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
		c1);

	ccColor4B c2 = {0xff, 0x00, 0x00, 0xff};
	AppDelegate::DrawLine(
		ccp(0, 0),
		ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
		c2);

	ccColor4B c3 = {0xff, 0x00, 0xff, 0xff};
	AppDelegate::DrawRect1(
		ccp(100, 100),
		ccp(AppDelegate::m_DebugSize.width - 100, AppDelegate::m_DebugSize.height - 100),
		c3);
}

void HelloWorld::update(float dt)
{
	
}