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
	//���������
	for (int i = 0; i < 8; ++i)
	{
		CCSprite* sprite = CCSprite::create("01.PNG");

		//sprite->setVisible(false);

		m_SpriteList.push_back(sprite);

		//����Ϊ��ǰ����ӽڵ�
		addChild(sprite);
	}

	//��������
	t1 = CCTextureCache::sharedTextureCache()->addImage("02.PNG");
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

	//�������о��鲻�ɼ�
	for (int i = 0; i < m_SpriteList.size(); ++i)
		m_SpriteList.at(i)->setVisible(false);
	m_CurUseSpriteIndex = 0;

	for (int i = 0; i < 10; ++i)
	{
		DrawTexture(
			t1,
			45.0f,
			CCSize(1.0f, 2.0f),
			ccp(rand() % 800, rand() % 600));
	}
}

void HelloWorld::update(float dt)
{
	Sleep(50000);
}

void HelloWorld::DrawTexture(CCTexture2D* t,
							 float angle,
							 CCSize scale,
							 CCPoint position)
{
	//����
	if (m_CurUseSpriteIndex == m_SpriteList.size())
	{
		for (int i = 0; i < 8; ++i)
		{
			CCSprite* sprite = CCSprite::create("01.PNG");

			sprite->setVisible(false);

			m_SpriteList.push_back(sprite);

			//����Ϊ��ǰ����ӽڵ�
			addChild(sprite);
		}
	}

	CCSprite* s = m_SpriteList.at(m_CurUseSpriteIndex);
	m_CurUseSpriteIndex += 1;

	//Ϊ�Ѿ�׼���õľ�����������
	s->setTexture(t);

	//���ýǶ�
	s->setRotation(angle);

	//����������
	s->setScaleX(scale.width * AppDelegate::m_Scale);
	s->setScaleY(scale.height * AppDelegate::m_Scale);

	//����λ��
	position.x *= AppDelegate::m_Scale;
	position.x += AppDelegate::m_OffsetX;
	position.y *= AppDelegate::m_Scale;
	position.y = AppDelegate::m_ReleaseSize.height - position.y;
	s->setPosition(position);

	//���ÿɼ�
	s->setVisible(true);
}