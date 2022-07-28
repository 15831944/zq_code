#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class CGameLayer : public CCLayer
{
private:

	//��������
	CGameLayer();
	virtual ~CGameLayer();

	//���롢�˳��������
	virtual void onEnter();
    virtual void onExit();
	virtual void onEnterTransitionDidFinish();

	//�������
	CCPoint m_Touches[32];
	int m_TouchesNum;
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* Event);
    virtual void ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent);

	//������
	virtual void draw();

	//�߼����
	virtual void update(float dt);

public:

	//����
	virtual void Enter();
	virtual void InputDown(CCPoint* p);
	virtual void InputMove(CCPoint* p, int n);
	virtual void InputUp(CCPoint* p);
	virtual void Output();
	virtual void Logic(float dt);
	virtual void Exit();

	//�������
	std::vector<CCSprite*> m_Sprites;
	void DrawLine(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawRect1(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawRect2(const CCPoint& p1, const CCPoint& p2, int c);
	void DrawImage1(
		CCTexture2D* t,
		int sx, int sy, int sw, int sh,
		int dx, int dy, int dw, int dh);
	void DrawImage2(
		CCTexture2D* t,
		float angle,
		int sx, int sy, int sw, int sh,
		int dx, int dy, int dw, int dh);
	void DrawString(
		int x, int y,
		int w, int h,
		int xn, int yn,
		const char* str);

	//�ļ����
	struct _FILE_DATA
	{
		char* fd; //�ļ��������׵�ַ
		int fs; //�ļ����ܴ�С
	};
	_FILE_DATA GetResourceFileData(const char* fn);
	const char* GetRWDirectory();

	//��Ƶ���
	void PlayMusic(const char* fn);
	void StopMusic();
	float GetMusicVolume();
	void SetMusicVolume(float v);
	void PlayEffect(const char* fn);
	float GetEffectVolume();
	void SetEffectVolume(float v);

	//UI���
};

#endif