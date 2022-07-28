#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class CGame : public cocos2d::CCLayer
{
public:

	//��ʼ��
	CGame();

	//��β
	~CGame();

	//���������������ת�������������ĳ���ʱ������
	virtual void onEnter();

	//������ӱ��������ĳ���ת������������ʱ������
    virtual void onExit();

	//��ǰ�л�����ִ����ϵ�ʱ�����ñ��������ڱ�
	//����û�б�����֮ǰ���������õ���ȥ�л�����
	virtual void onEnterTransitionDidFinish()
	{}
    
	//��㴥��
	CCPoint touch[32];
	int touch_num;
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void draw();

	virtual void update(float dt);

	//����
	MyTexture* t;

	//���ֻ���
	void DrawString(
		int x, int y, //���ֻ�����������Ͻ�x��y����
		int w, int h, //ÿ�����ֵĿ���
		int xn, int yn,  //���ֻ��������x��y�������������
		const char* str)
	{
		//���μ�������
		MyTexture* ascii = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("ASCII.PNG");

		//ѭ����������
		for (int i = 0; str[i] && i < xn * yn; ++i)
		{
			//�õ�Դ���־���
			int sx = (str[i] % 32) * 25;
			int sy = (str[i] / 32) * 48;

			//�õ�Ŀ�����־���
			int dx = (i % xn) * w;
			int dy = (i / xn) * h;

			ascii->Draw(
				sx, sy, 25, 48,
				dx + x, dy + y, w, h);
		}
	}
};

#endif