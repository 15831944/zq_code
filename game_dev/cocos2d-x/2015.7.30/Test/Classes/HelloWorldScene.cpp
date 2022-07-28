#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
	//��������
	auto scene = Scene::create();

	//����CREATE_FUNC���滻�����ľ�̬create����
	auto layer = HelloWorld::create();

	//���ñ������Ϊ�������ӽڵ�
	scene->addChild(layer);

	//���س���
	return scene;
}

bool HelloWorld::init()
{
	//���ø���ĳ�ʼ��
	if ( !Layer::init() )
	{
		return false;
	}

	//�õ����ڵĳߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�õ����ڵ����½�λ��
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//cocos2d����е���������ϵ�����л���
	//ʱ��ʹ�õ�����ϵ����GL����ϵ
	//UI����ϵ��x���ң�y����
	//GL����ϵ��x���ң�y����

	//����һ��ͼ��˵���
	closeItem = MenuItemImage::create(
		"close/CloseNormal.png", //�˵�δ������ʱ���ͼ��
		"close/CloseSelected.png", //�˵�������ʱ���ͼ��
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)); //�˵���Ӧ����

	//����ͼ��˵����λ��
	closeItem->setPosition(
		Vec2(
		//0 + 960 - 40 / 2 = 940
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		//0 + 40 / 2 = 20
		origin.y + closeItem->getContentSize().height / 2)
		);

	//�ٴ���1��ͼ��˵������Ȼѡ����menuCloseCallbackΪ��Ӧ����
	closeItem2 = MenuItemImage::create(
		"close/ok1.png",
		"close/ok2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem2->setPosition(
		//100 / 2 = 50
		closeItem2->getContentSize().width / 2,
		//60 / 2 = 30
		closeItem2->getContentSize().height / 2);

	kkk = MenuItemImage::create(
		"close/kkk1.png",
		"close/kkk2.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback2, this));
	kkk->setPosition(
		//100 / 2 = 50
		kkk->getContentSize().width / 2,
		//60 / 2  + = 30
		kkk->getContentSize().height / 2 + closeItem2->getContentSize().height);

	//ͨ�����е�ͼ��˵����һ���˵�������Ĳ˵��ľ�̬
	//����create��һ�������κ�����ǰ��Ӧ�����η���ͼ���
	//��������NULL��Ϊ�������������ı��ʾ��ǰ�ͼ���
	//����ͨ��addChild��������Ϊ�˵����ӽڵ㣬����Ĵ���
	//ִ�����֮��menu�����������ӽڵ�ֱ���closeItem��
	//closeItem2��kkk
	auto menu = Menu::create(closeItem, closeItem2, kkk, NULL);

	//���ò˵�λ��
	menu->setPosition(Vec2::ZERO); //Vec2::ZERO����Vec2(0.0f, 0.0f)
	
	//���˵�����Ϊ������ӽڵ㣬�ڶ������������ȼ������ȼ�
	//Խ����ô��Խ����ƣ���ô���ȼ��ߵľͻᵲס���ȼ��͵�
	this->addChild(menu, 1);

	//TTF��ָ��ture type fonts����һ�ֿ���������������α�����壬һ
	//����˵������������
	//1���������壬���������洢������һ����˵һ�����ֽھͿ��Դ洢
	//   ���������ˣ����ǵ������������ŵ�ʱ��������α䣬������Ĵ�
	//   ��������Bios�е��ֽھ��ǵ������壬�൱����һ���ڰ�λͼ
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//   ��������������������������������
	//2��truetype���壬������ͼ�ν����������е�һ�����壬�������岻��
	//   ���ֽڴ洢���ֵĵ���Ϣ�����Ǵ洢������ֵıʻ���Ҳ����˵�洢
	//   ����Ϣ���ƣ���(x1,y1)��(x2,y2)��ֱ�ߣ���(x3,y3)��(x4,y4)����
	//   �ߵȣ������Ĵ洢����ʹ�����κγߴ�����������ֵĻ��ƶ���ʧ��

	//������ǩ����ǩ������ʾһ�����ֵģ��൱����MFC�еľ�̬�ı����䱾��
	//�Ǹ������ִ���������һ��ͼƬ
	auto label = Label::createWithTTF(
		"Hello World", //��������
		"fonts/Marker Felt.ttf", //�����ļ�
		32); //�����С
	//�����СΪ32��ʱ��������ǩ�ߴ�Ϊ139*34
	//�����СΪ64��ʱ��������ǩ�ߴ�Ϊ276*68
	Size label_size = label->getContentSize();

	//���ñ�ǩλ��
	label->setPosition(
		Vec2(
		//0 + 960 / 2 = 480
		origin.x + visibleSize.width/2,
		//0 + 640 - 34 = 606
		origin.y + visibleSize.height - label->getContentSize().height
		));

	//���ñ�ǩΪ������ӽڵ�
	this->addChild(label, 1);

	//����һ�����飬������cocos2d�еĺ����࣬�������е���Ϸ����
	//Ԫ�ض������þ��������֣�����ı�����һ��ͼ����ϡ��任��
	//�͡���������������кܷḻ�ı���
	auto sprite = Sprite::create("HelloWorld.png");

	//���þ���λ��
	sprite->setPosition(
		Vec2(
		//960 / 2 + 0
		visibleSize.width/2 + origin.x,
		//640 / 2 + 0
		visibleSize.height/2 + origin.y)
		);

	//���þ���Ϊ������ӽڵ�
	this->addChild(sprite, 3);

	//�ڶ�������
	auto sprite2 = Sprite::create("s.png");
	sprite2->setPosition(Vec2(200.0f, 200.0f));
	this->addChild(sprite2, 0);

	//addChild�ĵڶ����������˻���˳��Խ�����
	//�ȼ���Խ����ƣ���������Ĵ����ǵ�һ������
	//�ڵ��˵ڶ�������

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//�����pSender���ǵ�ǰ������˵���ĵ�ַ��ʹ��
	//��֧ѡ�������Էǳ���������ֵ������Ǹ��˵���
	//�����

	if (pSender == closeItem)
		Director::getInstance()->end();
	else if (pSender == closeItem2)
		closeItem2->setVisible(false);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback2(cocos2d::Ref* pSender)
{
	//kkk����Ӧ����
}