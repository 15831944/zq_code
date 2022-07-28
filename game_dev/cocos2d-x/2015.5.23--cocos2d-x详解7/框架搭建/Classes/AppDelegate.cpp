#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Start.h"
#include "Game.h"

using namespace CocosDenshion;
using namespace cocos2d;

CCSize AppDelegate::m_DebugSize;
CCSize AppDelegate::m_ReleaseSize;
float AppDelegate::m_Scale;
float AppDelegate::m_OffsetX;
CCLayer* AppDelegate::m_Layer[32];
int AppDelegate::m_LayerNum;

AppDelegate::AppDelegate()
{}

AppDelegate::~AppDelegate()
{
	//�ͷ����еĲ�
	for (int i = 0; i < m_LayerNum; ++i)
		delete m_Layer[i];

    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(false);
    pDirector->setAnimationInterval(1.0 / 30.0);

	//�õ��ߴ�
	m_DebugSize.setSize(_DEBUG_W, _DEBUG_H);
	m_ReleaseSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	//�õ����ű���
	m_Scale = m_ReleaseSize.height / m_DebugSize.height;

	//�õ�X����ƫ����
	m_OffsetX = (m_ReleaseSize.width - m_DebugSize.width * m_Scale) / 2.0f;

	//�������в㲢���ó�ʼ�Ĳ�
	AddLayer(new CStart);
	AddLayer(new CGame);
	SetInitLayer(0);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

bool AppDelegate::AddLayer(CCLayer* layer)
{
	if (m_LayerNum == _MAX_LAYER)
		return false;
	m_Layer[m_LayerNum++] = layer;
	return true;
}

bool AppDelegate::SetInitLayer(int index)
{
	if (index < 0 || index >= m_LayerNum)
		return false;
	CCScene* scene = CCScene::create();
	scene->addChild(m_Layer[index]);
	CCDirector::sharedDirector()->runWithScene(CCTransitionFade::create(1.0f, scene));
}

bool AppDelegate::SetCurLayer(int index)
{
	if (index < 0 || index >= m_LayerNum)
		return false;
	CCScene* scene = CCScene::create();
	scene->addChild(m_Layer[index]);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, scene));
}