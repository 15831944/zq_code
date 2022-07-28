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

void PrintCCNodeTree(CCNode* p, int level)
{
	if (!p)
		return;

	//��ӡ��ǰ��Ĳ���
	char buf[256] = {};
	for (int i = 0; i < level; ++i)
		strcat_s(buf, 256, "��");
	OutputDebugStringA(buf);

	CCPoint a = CCPointZero;
	if (!p->isIgnoreAnchorPointForPosition())
		a = p->getAnchorPoint();
	
	//��ӡ��ǰ�ڵ�����
	sprintf_s(
		buf,
		256,
		"�ߴ�(%d,%d)λ��(%d,%d)ê��(%f,%f)\n",
		(int)p->getContentSize().width,
		(int)p->getContentSize().height,
		(int)p->getPosition().x,
		(int)p->getPosition().y,
		a.x,
		a.y);
	OutputDebugStringA(buf);

	//�ݹ������ӽڵ�
	//ÿ���ڵ��ڴ洢���ӽڵ��ʱ�����õ�һ��CCArray���洢
	//�ģ���CCArray�洢������������CCObject����CCObject����
	//��������cocos2d��ĸ��࣬����CCNodeҲ���Դ洢��CCArray
	//֮�У�ֻ��������Ҫ����CCNode��ʱ�����ǿת
	CCArray* arr = p->getChildren();
	for (int i = 0; i < (int)p->getChildrenCount(); ++i)
	{
		CCNode* q = (CCNode*)arr->objectAtIndex(i);
		PrintCCNodeTree(q, level + 1);
	}
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

	//��ӡ
	PrintCCNodeTree(pScene, 0);
	//�ߴ�(480,320)λ��(0,0)ê��(0,0)
	//���ߴ�(480,320)λ��(0,0)ê��(0,0)
	//�����ߴ�(480,320)λ��(0,0)ê��(0,0)
	//�������ߴ�(100,100)λ��(100,50)ê��(0.5,0)
	//���������ߴ�(40,80)λ��(50,100)ê��(0.5,0.5)
	//���������ߴ�(50,50)λ��(100,200)ê��(0,0.5)

	//�ߴ�(480,320)λ��(0,0)ê��(0.000000,0.000000)
	//���ߴ�(480,320)λ��(0,0)ê��(0.000000,0.000000)
	//�����ߴ�(480,320)λ��(0,0)ê��(0.000000,0.000000)
	//�������ߴ�(100,100)λ��(100,50)ê��(0.500000,0.000000)
	//���������ߴ�(40,80)λ��(50,100)ê��(0.500000,0.500000)
	//���������ߴ�(50,50)λ��(100,200)ê��(0.000000,0.500000)
	
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