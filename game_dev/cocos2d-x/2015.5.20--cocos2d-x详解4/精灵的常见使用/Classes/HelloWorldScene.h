#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:

	//��ʼ��
	HelloWorld();

	//��β
	~HelloWorld();

	//�õ���������ĳ���
    CCScene* getScene();

	//���������������ת�������������ĳ���ʱ������
	virtual void onEnter();

	//������ӱ��������ĳ���ת������������ʱ������
    virtual void onExit();

	//���������������ת�������������ĳ������ó�
	//�����ɶ���������£����ɶ�������ʱ������
    //virtual void onEnterTransitionDidFinish();

	//Ҫ�뿪�����������뽫��������Ϊ������Ϣ��
	//�ַ�Ŀ�꣬cocos2d�д�����Ϣ������һ����
	//��������������������ȵõ���������������
	//��ǰ�����е���Щ�����淢����Щ������Ϣ��
	//ֻ��ȷ��ĳ�����ǵ�ǰ�ķַ�Ŀ�꣬��ô����
	//�������Ż�Ѵ�����Ϣ��������㣬�������
	//Щ�麯�����ܱ����ã�һ�㶼��onEnter������
	//����Ϊ������Ϣ�ķַ�Ŀ��
    
    //��������ʱ������
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	//�����ƶ�ʱ������
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);

	//����̧��ʱ������
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);

	//������ϵͳȡ��ʱ������
    virtual void ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);

	//��дdraw����������ɱ���Ļ��ƣ�cocos2d����
	//����ÿ����Ϸѭ�������������draw����
	virtual void draw();

	//���º�����ֻҪ��onEnterͨ��scheduleUpdate����
	//���˱���Ҫ���и��£���ôcocos2d�������ÿ����
	//Ϸѭ�������������update�����������뵱ǰʱ��
	virtual void update(float dt);

	//����
	CCSprite* s1;
	float a;
	float sf;
	bool fd;
};

#endif