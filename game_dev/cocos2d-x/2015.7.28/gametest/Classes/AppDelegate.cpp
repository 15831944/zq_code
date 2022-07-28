#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;
//ע��cocos2d�������඼�������ֿռ�cocos2d�еģ�����
//ʹ�������Ǿ�꣨չ��Ϊusing namespace cocos2d;����
//cocos2d�����ֿռ��

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate() 
{}

void AppDelegate::initGLContextAttrs()
{
	//OpenGL��һ���ײ�ͼ�ο⣨ͬDirect3D���ƣ����ṩ��
	//�ܶ��ͼ����Ⱦ���ܣ�cocos2d-x�ĵײ���ƾ���ʹ�õ�
	//OpenGL���ϸ���˵��OpenGL��Ƕ��ʽ�汾OpenGLES����
	//�ڵ������ֻ��Կ����̻����϶����ֻ���ʵ����OpenGLES
	//�������Դ˴������û���������OpenGLʹ�õ����ظ�ʽ��
	//��ʵһ�㶼�����޸ģ�
   
	//���ظ�ʽ���洢һ���������õ������ݸ�ʽ������Ĵ���
	//GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
	//�Ľ������£�
	//8λ��ɫ����
	//8λ��ɫ����
	//8λ��ɫ����
	//8λAlpha���ͨ��
	//24λ��Ȼ���
	//8λģ�建��
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//auto
	//c99��׼�У���ʾ����ջ�ڴ��еı�����һ��
	//���Ƕ�ʡ���ˣ���������Ĵ���
	//int a = 1; //����������Ϊ��auto int a = 1;
	//auto�ı������Զ�������ı������Զ��ͷ�
	//�ڴ�ģ�Ҳ����֪�����������εı�������
	//ջ��
	//c11��׼�У���ʾ�ƶϵ���˼�����Զ�ʶ��
	//��ı������ͣ���������Ĵ���
	//auto a = 1.0; //���������ԴӺ���ĳ�ʼ�����ʽ�Ľ�������ƶϳ���a��double����
	//ע��c11�е�auto��c99�еĹ�����ȫ��ͬ��
	//c11����auto�����������Ҫ��ʼ�������
	//����ʼ������ô���޷��ƶ����͵�
	//auto a = 1.0; //�����ƶϳ���Ϊdouble
	//auto a; //����û�г�ʼ�����

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

	//�����ڴ˴�ͨ��OpenGL���ñ�д��Ϸʱ���
	//���ڴ�С��ע��cocos2d-x 3.xĬ�ϵı�д
	//��Ϸʱ��Ĵ��ڴ�СΪ960*640
	//glview->setFrameSize(640, 480);

	//�����Ƿ���ʾ֡״̬
    director->setDisplayStats(true);

    //����֡�ʣ���Ϸ����ν֡�ʾ���ֵ��ÿ���
	//��Ϸѭ��������һ����˵��ά��Ϸ��25֡/��
	//��40֡/�붼���ԣ���ά��Ϸһ����Ҫ60֡/��
    director->setAnimationInterval(1.0 / 30);

	//����Ĵ�����������޸�

    //��HelloWorld��ľ�̬��Ա����createScene
	//����һ������HelloWorld�����ĳ���
    auto scene = HelloWorld::createScene();

    //���ó�ʼ�ĳ���
    director->runWithScene(scene);

	OutputDebugStringA("applicationDidFinishLaunching\n");

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ������Ϸ����
    Director::getInstance()->stopAnimation();

    //���ʹ������Ƶ���棬��ôӦ�ü�������Ĵ���

	//��ͣ�������ֵĲ���
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	OutputDebugStringA("applicationDidEnterBackground\n");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ������Ϸ����
    Director::getInstance()->startAnimation();

    //���ʹ������Ƶ���棬��ôӦ�ü�������Ĵ���

	//�ָ��������ֵĲ���
    //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

	OutputDebugStringA("applicationWillEnterForeground\n");
}
