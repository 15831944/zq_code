#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld* AppDelegate::h;
Game* AppDelegate::g;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate() 
{
	delete g;
	delete h;
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//�õ����������
    auto director = Director::getInstance();

	//ͨ�����������õ�OpenGL����
    auto glview = director->getOpenGLView();

	//���û�еõ�OpenGL����
    if(!glview)
	{
		//����һ�����ֽ�My Game��OpenGL����
        glview = GLViewImpl::create("My Game");

		//��OpenGL�������õ������У����ݻ���
		//OpenGL���������л���
        director->setOpenGLView(glview);
    }

	//��֪���汾�������ʱ��ĳߴ�
	glview->setDesignResolutionSize(_DESIGN_W, _DESIGN_H, ResolutionPolicy::EXACT_FIT);

	//���ô��ڴ�СΪ���ʱ��ĳߴ�
	glview->setFrameSize(_DESIGN_W, _DESIGN_H);

	//�����Ƿ���ʾ֡״̬
    //director->setDisplayStats(true);

    //����֡�ʣ���Ϸ����ν֡�ʾ���ֵ��ÿ���
	//��Ϸѭ��������һ����˵��ά��Ϸ��25֡/��
	//��40֡/�붼���ԣ���ά��Ϸһ����Ҫ60֡/��
    director->setAnimationInterval(1.0 / 30);

	//������
	h = new HelloWorld;
	g = new Game;

	//�ó���װ�ز㲢�õ�������
	Scene* s = Scene::create();
	s->addChild(h);

	//��ʹ���л�����
    //director->runWithScene(s); //���ó�ʼ�ĳ���

	//cocos2d���ṩ�˺ܶ�Ķ����л��࣬���ǿ��԰���������
	//��������н��г����л�֮����ƶ�������Щ�����������
	//����TransitionScene�����࣬ʹ�÷�ʽ�����ڵ������ó�ʼ
	//�����������õ�ǰ�����ĺ����е�����Щ���create��������
	//����������create(����������Ŀ�곡��)
	director->runWithScene(TransitionFade::create(2.0f, s));

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ������Ϸ����
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ������Ϸ����
    Director::getInstance()->startAnimation();
}
