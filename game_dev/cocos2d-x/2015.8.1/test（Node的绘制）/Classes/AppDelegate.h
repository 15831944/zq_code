#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#define _DESIGN_W 640.0f
#define _DESIGN_H 480.0f

class AppDelegate : private cocos2d::Application
{
public:
	//����
    AppDelegate();

	//����
    virtual ~AppDelegate();

	//��ʼ��OpenGL�����ظ�ʽ
    virtual void initGLContextAttrs();

    //��ʼ����ʱ����ñ�����
    virtual bool applicationDidFinishLaunching();

	//��Ϸ��ǰ̨ת���̨��ʱ����ñ�����
    virtual void applicationDidEnterBackground();

	//��Ϸ�Ӻ�̨ת��ǰ̨��ʱ����ñ�����
    virtual void applicationWillEnterForeground();
};

#endif

//AppDelegate������Ӧ�ó���
//Director���������������ݣ�������Ҫ���𳡾�����

