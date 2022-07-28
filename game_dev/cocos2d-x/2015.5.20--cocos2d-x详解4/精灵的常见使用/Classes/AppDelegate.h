#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
using namespace cocos2d;

#define _DEBUG_W 800
#define _DEBUG_H 600

class AppDelegate : private cocos2d::CCApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

	static CCSize m_DebugSize; //����ʱ�����Ϸ���ڳߴ磬��Windows���ڳߴ�
	static CCSize m_ReleaseSize; //����ʱ�����Ϸ���ڳߴ磬���ֻ��ߴ�
	static float m_Scale; //����ֵ���������ߴ�/���Գߴ�
	static float m_OffsetX; //x�����ƫ����

	//�߶λ���
	static void DrawLine(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);

	//���ľ��λ���
	static void DrawRect1(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);

	//ʵ�ľ��λ���
	static void DrawRect2(
		const CCPoint& p1,
		const CCPoint& p2,
		ccColor4B c);
};

#endif
