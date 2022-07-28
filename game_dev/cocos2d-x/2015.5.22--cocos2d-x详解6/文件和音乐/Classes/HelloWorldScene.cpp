#include "HelloWorldScene.h"
#include "AppDelegate.h"
//......
//����n������ͼ��2

HelloWorld::HelloWorld()
{
	t1 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("01.PNG");
	t2 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("02.png");
	t3 = (MyTexture*)CCTextureCache::sharedTextureCache()->addImage("03.png");

	//cocos2d�ṩ��CCFileUtils�������������������ǲ����ļ�
	
	//�����Ҫ���ⲿ�ļ��ж�ȡ���ݣ���ô����Ӧ�ø����ļ���
	//�õ��ļ��ľ���·������ͨ��CCFileUtils�ṩ�Ķ�ȡ������
	//�õ��ļ�����
	const char* full_file_name = 
		CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("1.txt");

	res_d = full_file_name;

	file_data = CCFileUtils::sharedFileUtils()->getFileData(
		full_file_name, //������д����·��
		"rb",
		&file_size);
	//file_data��new unsigned char�õ��ģ��������һ��Ҫ����

	file_data[file_size - 1] = 0;

	hero = CCPointZero;
}	

HelloWorld::~HelloWorld()
{
	delete [] file_data;
}

CCScene* HelloWorld::getScene()
{
	CCScene* scene = CCScene::create();
	scene->addChild(this);
	return scene;
}

void HelloWorld::onEnter()
{
	//���ø����onEnter
	CCLayer::onEnter();

	//���ñ��㿪������
	setTouchEnabled(true);

	//��������ĸ���
	scheduleUpdate();

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/LoopyMusic.wav", true);
}

void HelloWorld::onExit()
{
	//���ø����onEnter
	CCLayer::onExit();
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
	began.clear();
	touch_num = 0;
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			began.push_back(touch[i]);
	}
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	touch_num = 0;
	move.clear();
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			move.push_back(touch[i]);
	}
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	touch_num = 0;
	end.clear();
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it)
	{
		CCPoint point = ((CCTouch*)(*it))->getLocationInView();
		if (point.x > AppDelegate::m_OffsetX && point.x < (AppDelegate::m_ReleaseSize.width - AppDelegate::m_OffsetX))
		{
			point.x -= AppDelegate::m_OffsetX;
			point.x /= AppDelegate::m_Scale;
			point.y /= AppDelegate::m_Scale;
			touch[touch_num++] = point;
		}
	}
	if (touch_num > 0)
	{
		for (int i = 0; i < touch_num; ++i)
			end.push_back(touch[i]);

		if (touch[0].x > 400 && touch[0].x < 500 &&
			touch[0].y > 400 && touch[0].y < 500)
		{
			//�õ����Խ���д����ļ�Ŀ¼
			std::string s = CCFileUtils::sharedFileUtils()->getWriteablePath();
			s += "/my_save";
			FILE* pf = fopen(s.c_str(), "wb");
			fwrite(&hero.x, 1, 4, pf);
			fwrite(&hero.y, 1, 4, pf);
			fclose(pf);

			wr_d = s;
		}
		else if (touch[0].x > 500 && touch[0].x < 600 &&
			touch[0].y > 400 && touch[0].y < 500)
		{
			std::string s = CCFileUtils::sharedFileUtils()->getWriteablePath();
			s += "/my_save";
			FILE* pf = fopen(s.c_str(), "rb");
			if (pf)
			{
				fread(&hero.x, 1, 4, pf);
				fread(&hero.y, 1, 4, pf);
				fclose(pf);
			}
		}
		else
		{
			SimpleAudioEngine::sharedEngine()->playEffect("sound/ding.wav");
			hero = touch[0];
		}
	}
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}

//���Լ�Ҳ���л���
void HelloWorld::draw()
{
	ccColor4B c = {0xff, 0xff, 0xff, 0xff};
	AppDelegate::DrawRect2(
		ccp(0, 0),
		ccp(AppDelegate::m_DebugSize.width, AppDelegate::m_DebugSize.height),
		c);

	//��ӡ���ֻ���Ļ��
	char buf[256];
	for (int i = 0; i < began.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)began[i].x, (int)began[i].y);
		DrawString(
			i * 200, 0,
			20, 40,
			10, 1,
			buf);
	}
	for (int i = 0; i < move.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)move[i].x, (int)move[i].y);
		DrawString(
			i * 200, 50,
			20, 40,
			10, 1,
			buf);
	}
	for (int i = 0; i < end.size(); ++i)
	{
		sprintf(buf, "(%d,%d)", (int)end[i].x, (int)end[i].y);
		DrawString(
			i * 200, 100,
			20, 40,
			10, 1,
			buf);
	}

	DrawString(
			0, 300,
			20, 40,
			50, 1,
			(char*)file_data);

	t1->Draw(0, 0, 100, 100, 400, 400, 100, 100);
	t2->Draw(0, 0, 100, 100, 500, 400, 100, 100);

	t3->Draw(0, 0, 100, 100, hero.x, hero.y, 100, 100);

	if (res_d.size() > 0)
	{
		DrawString(
			0, 500,
			10, 20,
			50, 1,
			res_d.c_str());
	}

	if (wr_d.size() > 0)
	{
		DrawString(
			0, 550,
			10, 20,
			50, 1,
			wr_d.c_str());
	}
}

void HelloWorld::update(float dt)
{
	
}