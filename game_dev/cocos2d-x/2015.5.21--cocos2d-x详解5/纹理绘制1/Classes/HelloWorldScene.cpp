#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//����n������ͼ��2

HelloWorld::HelloWorld()
{
	t1 = CCTextureCache::sharedTextureCache()->addImage("01.PNG");
	t2 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");
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

	//���Ҫ�ڻ��������ʱ�������ת������ô�ͱ���
	//�ڻ��Ƶ�ʱ�������һ�������ϵ�һ�����þ�
	//�����ת�Ƕȣ����ν��л��ƣ������������ת��ô
	//ֱ�ӽ���������Ƽ���

	//ֱ����ָ��λ�û�������
	t1->drawAtPoint(ccp(200, 200));

	//CCRect��cocos2d�����ڴ���һ����Ļ�ϵľ��ε���
	CCRect r;

	//origin��ʾ���ε����½ǵ�
	r.origin.x = 100;
	r.origin.y = 100;

	//size��ʾ���εĿ��
	r.size.width = 300;
	r.size.height = 150;

	//ֱ����Ŀ����л����������죩
	t2->drawInRect(r);
}

void HelloWorld::update(float dt)
{
	
}