#include "HelloWorldScene.h"
#include "Test.h"

HelloWorld::HelloWorld()
{
	int x = add(1, 2);
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

	//��ʼ����Ϸ����
	hero_pos = CCPointZero;
	move_right = true;
}

void HelloWorld::onExit()
{
	//���ø����onEnter
	CCLayer::onExit();
}

bool HelloWorld::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	//pTouch->getLocation(); //�õ�����GL����ϵ�µĴ�������
	//pTouch->getLocationInView(); //�õ�����UI����ϵ�µĴ�������
	
	return true;
}

void HelloWorld::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
	
}

void HelloWorld::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	hero_pos = pTouch->getLocation();
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

	ccColor4F cf0 = {0.3f, 0.3f, 0.3f, 0.1f};
	ccDrawSolidRect(ccp(0, 0), ccp(800, 600), cf0);

	//���õ�ǰ��ɫΪ��ɫ
	ccDrawColor4B(0xff, 0, 0, 0xff);

	//�߶λ���
	ccDrawLine(ccp(0, 0), ccp(300, 150));

	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
	ccDrawLine(ccp(0, 150), ccp(300, 0));

	//�ڹ���ģ�ͼ����У�������0~1֮��ĸ�����
	//����ʾһ����ɫ�ķ�����0~1���൱��������
	//�����ַ�������ɫ����ʱ���0~255����ôһ
	//����ɫ�Ϳ����ã�1.0f, 0.0f, 0.0f, 1.0f��
	//����ʾ
	ccDrawColor4F(0.0f, 1.0f, 1.0f, 1.0f);
	ccDrawLine(ccp(0, 150), ccp(300, 150));

	//���ľ��λ���
	ccDrawRect(ccp(200, 100), ccp(400, 300));

	//ʵ�ľ��λ���
	ccColor4F cf1 = {1.0f, 1.0f, 0.0f, 0.1f};
	ccDrawSolidRect(ccp(250, 150), ccp(450, 350), cf1);

	//ʵ�ľ��λ���
	ccColor4F cf2 = {1.0f, 0.0f, 0.0f, 0.3f};
	ccDrawSolidRect(ccp(300, 200), ccp(600, 400), cf2);

	//���� = ���� / �뾶����һ�ֱ�ʾ�Ƕȴ�С�ĵ�λ��90��ĽǶ�
	//�Ļ���ֵΪ3.1415926f / 2.0f��180��ĽǶȵĻ���ֵΪ3.1415926f��
	//360��ĽǶȵĻ���ֵΪ3.1415926f * 2.0f

	//�ȱ��λ���
	ccDrawCircle(
		hero_pos, //���ĵ�
		80.0f, //�뾶
		0.0f, //�Ƕ�
		8, //����
		true); //�Ƿ�����ߵ����ĵ�
}

void HelloWorld::update(float dt)
{
	if (move_right)
	{
		hero_pos.x += 10;
		if (hero_pos.x > 800)
			move_right = false;
	}
	else
	{
		hero_pos.x -= 10;
		if (hero_pos.x < 0)
			move_right = true;
	}
}