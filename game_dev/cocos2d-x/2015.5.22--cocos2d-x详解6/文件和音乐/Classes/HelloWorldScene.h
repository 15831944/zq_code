#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
    
	//��㴥��
	CCPoint touch[32];
	int touch_num;
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	std::vector<CCPoint> began, move, end;

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
	MyTexture* t3;

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

	unsigned long file_size;
	unsigned char* file_data;

	CCPoint hero;

	std::string res_d, wr_d;
};

#endif

//SimpleAudioEngine��һ�������࣬������Ƶ�Ĳ��ţ���������
//һ��ֻ�ܲ���һ������Чͬһʱ������ж������

//���ű������֣��ڶ������ж��Ƿ�ѭ��
//void playBackgroundMusic(const char* pszFilePath, bool bLoop);

//ֹͣ�������ֲ��ţ������ж��Ƿ��ͷ�����
//void stopBackgroundMusic(bool bReleaseData);

//��ͣ��������
//void pauseBackgroundMusic();

//�ָ���������
//void resumeBackgroundMusic();

//��ȡ���ñ�����������
//float getBackgroundMusicVolume();
//void setBackgroundMusicVolume(float volume);

//��ȡ������Ч����
//float getEffectsVolume();
//void setEffectsVolume(float volume);

//������Ч�����ش������Ч��id
//unsigned int playEffect(const char* pszFilePath, bool bLoop);

//��ָͣ����Ч��������Ч
//void pauseEffect(unsigned int nSoundId);
//void pauseAllEffects();

//�ָ�ָ����Ч��������Ч
//void resumeEffect(unsigned int nSoundId);
//void resumeAllEffects();

//ָֹͣ����Ч��������Ч
//void stopEffect(unsigned int nSoundId);
//void stopAllEffects();