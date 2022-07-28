#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate()
{
	//��������Ƶ��������й���
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	//�õ���ǰ���������
	CCDirector* pDirector = CCDirector::sharedDirector();

	//����OpenGL��������ڻ�ͼ
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	//������ʾ֡��
	pDirector->setDisplayStats(true);

	//������Ϸ֡��
	pDirector->setAnimationInterval(1.0 / 30);

	//HelloWorld������һ���������󣬲��ҽ��Լ�
	//װ������������󲢷��أ�ע��HelloWorld��
	//�����ǳ��������ǲ㣬��������������롢
	//������߼������������Լ��������еĳ�����
	//����cocos2d-x�ĵ��ݲ���ֱ������һ���㣬��
	//ֻ��ֱ������һ����������������Ҫ����һ��
	//��ͱ��뽫һ����װ�뵽һ�����������õ���
	//�����������������ӵ������������
	CCScene* pScene = HelloWorld::scene();
	
	//���ó�ʼ���еĳ���
	pDirector->runWithScene(pScene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ������Ϸ�Ļ���
	CCDirector::sharedDirector()->stopAnimation();

	//ֹͣ������Ϸ�ı������ֲ���
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ������Ϸ�Ļ���
	CCDirector::sharedDirector()->startAnimation();

	//�ָ�������Ϸ�ı������ֲ���
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}