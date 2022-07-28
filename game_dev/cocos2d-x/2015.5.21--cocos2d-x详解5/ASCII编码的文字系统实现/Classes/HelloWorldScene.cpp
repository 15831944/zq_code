#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//����n������ͼ��2

HelloWorld::HelloWorld()
{
	t1 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("01.PNG");
	t2 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("02.png");
	pos = CCPointZero;
}

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
	pos = pTouch->getLocationInView();
}

void HelloWorld::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{

}

//���Լ�Ҳ���л���
void HelloWorld::draw()
{
	ccColor4B c = {0xff, 0xff, 0xff, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(500, 500),
		c);

	t1->Draw(
		0, 0, 100, 100,
		0, 0, AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height);

	t2->Draw(
		25, 25, 50, 50,
		pos.x, pos.y, 200, 200);

	DrawString(
		100, 100,
		30, 50,
		3, 3,
		"abcdefghijklmn");
}

void HelloWorld::update(float dt)
{
	
}