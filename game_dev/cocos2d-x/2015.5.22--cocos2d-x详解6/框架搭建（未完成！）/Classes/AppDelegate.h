#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
using namespace cocos2d;

#define _DEBUG_W 800
#define _DEBUG_H 600
#define _MAX_LAYER 32

class AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

	//����Ӧ��Ļ���
	static CCSize m_DebugSize; //����ʱ�����Ϸ���ڳߴ磬��Windows���ڳߴ�
	static CCSize m_ReleaseSize; //����ʱ�����Ϸ���ڳߴ磬���ֻ��ߴ�
	static float m_Scale; //����ֵ���������ߴ�/���Գߴ�
	static float m_OffsetX; //x�����ƫ����

	//�����������
	static CCLayer* m_Layer[_MAX_LAYER];
	static int m_LayerNum;
	static bool AddLayer(CCLayer* layer);
	static bool SetInitLayer(int index);
	static bool SetCurLayer(int index);
};

#endif
