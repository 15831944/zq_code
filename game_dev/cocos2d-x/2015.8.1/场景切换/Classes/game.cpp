#include "Game.h"
#include "AppDelegate.h"

Game::Game()
{
	//�����˵�
	MenuItemImage* c = MenuItemImage::create(
		"h0.png",
		"h1.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));
	c->ignoreAnchorPointForPosition(true);
	Menu* m = Menu::create(c, NULL);
	m->setPosition(Vec2::ZERO);
	this->addChild(m, 2);

	//��������
	s = Sprite::create("3.png");
	s->setPosition(Vec2(320, 240));

	this->addChild(s);
}

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	//�л�����
	Scene* s = Scene::create();
	s->addChild(AppDelegate::h);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, s)); //���õ�ǰ����

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}