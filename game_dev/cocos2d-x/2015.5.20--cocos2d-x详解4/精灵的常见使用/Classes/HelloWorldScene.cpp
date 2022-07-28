#include "HelloWorldScene.h"
#include "AppDelegate.h"

//����Ŀ���
//ê���Ǿ�����ͼ�α任ʱ�����Ҫ�Ĳο���������
//����ת��ʱ��ê���൱�������š���ת������ԭ
//�㣬�������ȿ���û�б任��ʱ�򣬻��Ƶ���Ļ��
//��������Ȼ������Ļ�����ҵ�ê�㣨����ê�㲢
//������û��ê�㣩����ê����Ϊ����ԭ�����ͼ��
//�任��ͼ�α任��˳����������setScale��setRotation
//��ת��ƽ��setPosition
//�ڳ��������Ҫ���ֶ��ʹ��ͬһͼ��Ļ��棬��
//ô����Ҫʹ�ö�����飬ÿ�������ж���ͼ����
//����Դ��һ��ָ�룬cocos2d-xר��ʹ��ͼ�񻺳�
//�������������õ���ͼ��������£�
//ͼ�񻺳��ࣺͼ��1��ͼ��2��...��ͼ��n
//����1������ͼ��1
//����2������ͼ��1
//����3������ͼ��2
//......
//����n������ͼ��2

HelloWorld::HelloWorld()
{
	s1 = CCSprite::create("01.PNG");
	//s1->ignoreAnchorPointForPosition(true);
	s1->setAnchorPoint(ccp(1.0, 0.0));
	this->addChild(s1);

	CCTexture2D* t2 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");
	s1->setTexture(t2);

	//s1->setVisible(false);

	a = 0.0f;
	sf = 1.0f;
	fd = true;
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
	ccColor4B c = {0xff, 0xff, 0x00, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(500, 500),
		c);
}

void HelloWorld::update(float dt)
{
	a -= 1.0f;

	////����
	//if (fd)
	//{
	//	sf += 0.01f;
	//	if (sf > 3.0f)
	//		fd = false;
	//}
	//else
	//{
	//	sf -= 0.01f;
	//	if (sf < 0.333f)
	//		fd = true;
	//}
	//s1->setScale(sf);

	

	////��ת
	s1->setRotation(a);

	s1->setScaleX(1.0f);
	s1->setScaleY(2.0f);

	s1->setPosition(ccp(300, 300));
}