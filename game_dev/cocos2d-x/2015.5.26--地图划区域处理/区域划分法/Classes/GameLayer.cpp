#include "UI.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define _INIT_SPRITE_NUM 4

//��cocos2d�����CCTexture2D��������
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

CGameLayer::CGameLayer()
{
	//�õ���д�ļ���Ŀ¼·��
	std::string s = CCFileUtils::sharedFileUtils()->getWriteablePath();
	strcpy(m_RWDirectory, s.c_str());

	//���ñ�Ե��ɫΪ��ɫ
	m_BorderColor = 0x000000ff;

	//�������ڻ��Ƶľ���
	for (int i = 0; i < _INIT_SPRITE_NUM; ++i)
	{
		//ͨ��Ĭ�ϵ�ͼ�񴴽�����
		CCSprite* sprite = CCSprite::create("Default/S_DEFAULT.PNG");

		//���þ�����Ϊ������ӽڵ�
		addChild(sprite);

		//������������
		m_Sprites.push_back(sprite);
	}
}

CGameLayer::~CGameLayer()
{
	for (int i = 0; i < (int)m_UI.size(); ++i)
		delete m_UI[i];
}

void CGameLayer::onEnter()
{
	//���ø����onEnter
	CCLayer::onEnter();

	//���ñ��㿪������
	setTouchEnabled(true);

	//��������ĸ���
	scheduleUpdate();

	//�����߼�ִ�б�־Ϊ��
	m_Logic = false;

	//��ʼ����ǰ�����±�Ϊ0
	m_CurSpriteIndex = 0;

	Enter();

	//����UI�����뺯��
	for (int i = 0; i < (int)m_UI.size(); ++i)
		m_UI[i]->Enter();
}

void CGameLayer::onExit()
{
	//����UI���ó�����
	for (int i = 0; i < (int)m_UI.size(); ++i)
		m_UI[i]->Exit();

	Exit();

	//���ø����onEnter
	CCLayer::onExit();
}

void CGameLayer::onEnterTransitionDidFinish()
{
	m_Logic = true;
}

void CGameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
	{
		//UI��Ӧ
		bool ui_click = false;
		for (int i = 0; i < (int)m_UI.size(); ++i)
		{
			if (m_UI[i]->m_Visible && m_UI[i]->m_Active)
			{
				//�ж��Ƿ����ڲ�
				if (m_Touches[0].x >= m_UI[i]->m_Rect.origin.x &&
					m_Touches[0].x < m_UI[i]->m_Rect.origin.x + m_UI[i]->m_Rect.size.width &&
					m_Touches[0].y >= m_UI[i]->m_Rect.origin.y &&
					m_Touches[0].y < m_UI[i]->m_Rect.origin.y + m_UI[i]->m_Rect.size.height)
				{
					m_UI[i]->OnMessage(_UE_IN_DOWN, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
					ui_click = true;
				}
				else
					m_UI[i]->OnMessage(_UE_OUT_DOWN, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
			}
		}

		if (!ui_click)
			InputDown(m_Touches);
	}
}

void CGameLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
		InputMove(m_Touches, m_TouchesNum);
}

void CGameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* Event)
{
	m_TouchesNum = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			m_Touches[m_TouchesNum++] = point;
		}
	}
	if (m_TouchesNum > 0)
	{
		//UI��Ӧ
		bool ui_click = false;
		for (int i = 0; i < (int)m_UI.size(); ++i)
		{
			if (m_UI[i]->m_Visible && m_UI[i]->m_Active)
			{
				//�ж��Ƿ����ڲ�
				if (m_Touches[0].x >= m_UI[i]->m_Rect.origin.x &&
					m_Touches[0].x < m_UI[i]->m_Rect.origin.x + m_UI[i]->m_Rect.size.width &&
					m_Touches[0].y >= m_UI[i]->m_Rect.origin.y &&
					m_Touches[0].y < m_UI[i]->m_Rect.origin.y + m_UI[i]->m_Rect.size.height)
				{
					m_UI[i]->OnMessage(_UE_IN_UP, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
					ui_click = true;
				}
				else
					m_UI[i]->OnMessage(_UE_OUT_UP, m_Touches[0].x - m_UI[i]->m_Rect.origin.x, m_Touches[0].y - m_UI[i]->m_Rect.origin.y);
			}
		}

		if (!ui_click)
			InputUp(m_Touches);
	}
}

void CGameLayer::ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent)
{}

void CGameLayer::draw()
{
	Output();

	//����UI
	for (int i = 0; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_Visible)
			m_UI[i]->Render();
	}

	//�õ��߽���ɫ�ĸ�������ʾ
	ccColor4F color
		=
	{
		(m_BorderColor >> 24 & 0xff) / 255.0f,
		(m_BorderColor >> 16 & 0xff) / 255.0f,
		(m_BorderColor >> 8 & 0xff) / 255.0f,
		(m_BorderColor & 0xff) / 255.0f
	};

	//�õ���Ϸ�����ȡ��߽���ο��
	float game_w = AppDelegate::m_DebugSize.width * AppDelegate::m_ReleaseSize.height / AppDelegate::m_DebugSize.height;
	float border_w = (AppDelegate::m_ReleaseSize.width - game_w) / 2.0f;

	//���Ʊ߽�
	ccDrawSolidRect(
		ccp(0, 0),
		ccp(border_w, AppDelegate::m_ReleaseSize.height),
		color);
	ccDrawSolidRect(
		ccp(AppDelegate::m_ReleaseSize.width - border_w, 0),
		ccp(AppDelegate::m_ReleaseSize.width, AppDelegate::m_ReleaseSize.height),
		color);
}

void CGameLayer::update(float dt)
{
	//�������о���Ϊ���ɼ�
	for (int i = 0; i < (int)m_Sprites.size(); ++i)
		m_Sprites[i]->setVisible(false);

	//���õ�ǰ�����±�Ϊ0
	m_CurSpriteIndex = 0;

	if (m_Logic)
		Logic(dt);
}

void CGameLayer::Enter(){}
void CGameLayer::InputDown(CCPoint* p){}
void CGameLayer::InputMove(CCPoint* p, int n){}
void CGameLayer::InputUp(CCPoint* p){}
void CGameLayer::Output(){}
void CGameLayer::Logic(float dt){}
void CGameLayer::Exit(){}
void CGameLayer::Quit()
{
	CCDirector::sharedDirector()->end();
}

void CGameLayer::SetBorderColor(int BorderColor)
{
	m_BorderColor = BorderColor;
}
void CGameLayer::DrawLine(const CCPoint& p1, const CCPoint& p2, int c)
{
	//���ݴ����UI����ϵ��y����õ�GL����ϵ��y����
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;

	//�õ����Ƶ��߶ε�GL����ϵ������
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	
	//���õ�ǰ������ɫ
	ccDrawColor4B((c >> 24 & 0xff), (c >> 16 & 0xff), (c >> 8 & 0xff), c & 0xff);
	
	//�����߶�
	ccDrawLine(p3, p4);

	//�ָ���ɫ
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}
void CGameLayer::DrawRect1(const CCPoint& p1, const CCPoint& p2, int c)
{
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	ccDrawColor4B((c >> 24 & 0xff), (c >> 16 & 0xff), (c >> 8 & 0xff), c & 0xff);
	ccDrawRect(p3, p4);
	ccDrawColor4B(0xff, 0xff, 0xff, 0xff);
}
void CGameLayer::DrawRect2(const CCPoint& p1, const CCPoint& p2, int c)
{
	float p1y = AppDelegate::m_DebugSize.height - p1.y;
	float p2y = AppDelegate::m_DebugSize.height - p2.y;
	CCPoint p3 = ccp(p1.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p1y * AppDelegate::m_Scale);
	CCPoint p4 = ccp(p2.x * AppDelegate::m_Scale + AppDelegate::m_OffsetX, p2y * AppDelegate::m_Scale);
	ccColor4F cf
		=
	{
		(float)(c >> 24 & 0xff) / 255.0f,
		(float)(c >> 16 & 0xff) / 255.0f,
		(float)(c >> 8 & 0xff) / 255.0f,
		(float)(c & 0xff) / 255.0f
	};
	ccDrawSolidRect(p3, p4, cf);
}
void CGameLayer::DrawImage1(CCTexture2D* t,
							int sx, int sy, int sw, int sh,
							int dx, int dy, int dw, int dh)
{
	MyTexture* mt = (MyTexture*)t;
	mt->Draw(
		sx, sy, sw, sh,
		dx, dy, dw, dh);
}
void CGameLayer::DrawImage2(CCTexture2D* t,
							float angle,
							int dx, int dy, int dw, int dh)
{
	//���û�о����˾ʹ���һЩ����
	if (m_CurSpriteIndex == m_Sprites.size())
	{
		for (int i = m_Sprites.size() * 2; i > 0; --i)
		{
			//ͨ��Ĭ�ϵ�ͼ�񴴽�����
			CCSprite* sprite = CCSprite::create("Default/S_DEFAULT.PNG");

			//���þ�����Ϊ������ӽڵ�
			addChild(sprite);

			//���þ��鲻�ɼ�
			sprite->setVisible(false);

			//װ�����
			m_Sprites.push_back(sprite);
		}
	}

	//�õ�һ������
	CCSprite* s = m_Sprites[m_CurSpriteIndex++];

	//���þ��������
	s->setTexture(t);

	//�õ����������
	s->setScaleX((dw * AppDelegate::m_Scale) / 128.0f);
	s->setScaleY((dh * AppDelegate::m_Scale) / 128.0f);

	//�õ��������ת
	s->setRotation(angle);

	//�õ������λ��
	s->setPosition(
		ccp(
		dx * AppDelegate::m_Scale + AppDelegate::m_OffsetX + dw * AppDelegate::m_Scale / 2.0f,
		AppDelegate::m_ReleaseSize.height - (dy * AppDelegate::m_Scale + dh * AppDelegate::m_Scale / 2.0f)
		));

	//���þ���ɼ�
	s->setVisible(true);
}
void CGameLayer::DrawString(int x, int y,
							int w, int h,
							int xn, int yn,
							const char* str)
{
	//���μ�������
	MyTexture* ascii = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("Default/ASCII.PNG");

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

CGameLayer::_FILE_DATA CGameLayer::GetResourceFileData(const char* fn)
{
	_FILE_DATA fd = {};

	//�õ��ļ�����������
	const char* afn = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fn);
	if (!afn)
		return fd;

	//�õ��ļ�����
	unsigned long file_size;
	unsigned char* file_data = CCFileUtils::sharedFileUtils()->getFileData(afn, "rb", &file_size);

	fd.fd = (char*)file_data;
	fd.fs = file_size;

	return fd;
}
const char* CGameLayer::GetRWDirectory()
{
	return m_RWDirectory;
}

void CGameLayer::PlayMusic(const char* fn)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fn, true);
}
void CGameLayer::StopMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
}
float CGameLayer::GetMusicVolume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}
void CGameLayer::SetMusicVolume(float v)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(v);
}
void CGameLayer::PlayEffect(const char* fn)
{
	SimpleAudioEngine::sharedEngine()->playEffect(fn, false);
}
float CGameLayer::GetEffectVolume()
{
	return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}
void CGameLayer::SetEffectVolume(float v)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(v);
}

bool CGameLayer::LoadUI(int id, CUI* pUI)
{
	//���id�Ƿ����ظ�
	for (int i = 0; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			return false;
	}

	//����id��
	pUI->m_ID = id;

	//���ò�
	pUI->m_Layer = this;

	//װ�����
	m_UI.push_back(pUI);

	return true;
}

bool CGameLayer::ReleaseUI(int id)
{
	//�õ�ָ��id��UI
	int i = 0;
	for (; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			break;
	}

	//�ͷ�
	if (i < (int)m_UI.size())
	{
		delete m_UI[i];
		m_UI.erase(m_UI.begin() + i);
		return true;
	}
	else
		return false;
}

CUI* CGameLayer::GetUI(int id)
{
	int i = 0;
	for (; i < (int)m_UI.size(); ++i)
	{
		if (m_UI[i]->m_ID == id)
			return m_UI[i];
	}
	return 0;
}

void CGameLayer::OnUIMessage(int id, int msg){}