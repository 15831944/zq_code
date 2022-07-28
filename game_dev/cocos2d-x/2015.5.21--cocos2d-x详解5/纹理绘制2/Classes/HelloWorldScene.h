#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class MyTexture : public CCTexture2D
{
public:

	//���궼��UI����ϵ
	void Draw(
		int sx, int sy, int sw, int sh, //Դ����
		int dx, int dy, int dw, int dh) //Ŀ�����
	{
		//�õ�������
		float tw = getContentSize().width;
		float th = getContentSize().height;

		//����Դ��������4������ı���
		//sx / tw, (sy + sh) / th
		//(sx + sw) / tw, (sy + sh) / th
		//sx / tw, sy / th
		//(sx + sw) / tw, sy / th

		//����Դ���α���
		GLfloat coordinates[]
		=
		{    
			sx / tw, (sy + sh) / th,
			(sx + sw) / tw, (sy + sh) / th,
			sx / tw, sy / th,
			(sx + sw) / tw, sy / th
		};

		//����Ŀ�����λ��
		GLfloat vertices[] =
		{
			dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - (dy + dh)) * AppDelegate::m_Scale,
			(dx + dw) * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - (dy + dh)) * AppDelegate::m_Scale,
			dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - dy) * AppDelegate::m_Scale,
			(dx + dw) * AppDelegate::m_Scale + AppDelegate::m_OffsetX, (AppDelegate::m_DebugSize.height - dy) * AppDelegate::m_Scale
		};

		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
		m_pShaderProgram->use();
		m_pShaderProgram->setUniformForModelViewProjectionMatrix();
		ccGLBindTexture2D(m_uName);
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, coordinates);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
};

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
	MyTexture* t1;
	MyTexture* t2;
	CCPoint pos;
};

#endif