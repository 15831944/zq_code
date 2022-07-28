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
	//����Ϊ��ǰ����ӽڵ�
	s1 = CCSprite::create("01.PNG");
	addChild(s1);

	//��������
	t1 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");

	//s1->setTexture(t1);
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

	CCSize s(1.0f, 1.0f);
	DrawTexture(
		t1,
		45.0f,
		s,
		ccp(200, 200));

	CCSize s2(2.0f, 2.0f);
	DrawTexture(
		t1,
		90.0f,
		s2,
		ccp(400, 400));
}

void HelloWorld::update(float dt)
{
	
}

void HelloWorld::DrawTexture(CCTexture2D* t,
							 float angle,
							 CCSize scale,
							 CCPoint position)
{
	//Ϊ�Ѿ�׼���õľ�����������
	s1->setTexture(t);

	//���ýǶ�
	s1->setRotation(angle);

	//����������
	s1->setScaleX(scale.width * AppDelegate::m_Scale);
	s1->setScaleY(scale.height * AppDelegate::m_Scale);

	//����λ��
	position.x *= AppDelegate::m_Scale;
	position.x += AppDelegate::m_OffsetX;
	position.y *= AppDelegate::m_Scale;
	position.y = AppDelegate::m_ReleaseSize.height - position.y;
	s1->setPosition(position);
}