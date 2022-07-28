#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"

class AppDelegate : private cocos2d::CCApplication
{
public:
	//����
	AppDelegate();

	//����
	virtual ~AppDelegate();

	//��Ϸ��ʼ����ʱ�򱻵���
	virtual bool applicationDidFinishLaunching();

	//��Ϸ��ǰ̨ת�뵽��̨��ʱ�򱻵���
	virtual void applicationDidEnterBackground();

	//��Ϸ�Ӻ�̨ת�뵽ǰ̨��ʱ�򱻵���
	virtual void applicationWillEnterForeground();
};

#endif

//cocos2d-x�У�����ĳ������sharedXXX��
//��̬��Ա�����Ļ�������඼�ǵ�����

//AppDelegate������Ӧ�ó������������Լ���
//             CGameEngine��������ĺ����ڳ�
//             �������ڼ��ִ��˳�����£�
//1)applicationWillEnterForeground
//2)applicationDidFinishLaunching
//3)�����ǰ̨ת���̨��ô����applicationDidEnterBackground
//  ����Ӻ�̨ת��ǰ̨��ô����applicationWillEnterForeground

//CCDirector�������࣬�ǹ���ǰ�������е��࣬������
//            �Ե�ǰ����ʾ��֡�ʵ����ݽ��п��ƣ���Ϸ
//            ����������ͨ�����������л����л�������
//            �쵽�ģ����������Լ�CGameEngine�еĳ���
//            �����֣���һ��������
//sharedDirector��static�����õ�������Ϸ�е�Ψһ��һ�����������
//stopAnimation��ֹͣ������Ϸ�Ļ���
//startAnimation����ʼ������Ϸ�Ļ���
//setOpenGLView������OpenGL��������ڻ�ͼ
//setDisplayStats��������ʾ֡�����
//setAnimationInterval��������Ϸ֡��
//runWithScene�����ó�ʼ���еĳ���
//end��������Ϸ

//SimpleAudioEngine������Ƶ������
//end��static������������Ƶ��������й���
//sharedEngine��static�����õ�������Ϸ�е�Ψһ��һ������Ƶ���������
//pauseBackgroundMusic����ͣ������Ϸ�ı������ֲ���
//resumeBackgroundMusic���ָ�������Ϸ�ı������ֲ���

//CCEGLView��OpenGL��
//sharedOpenGLView��static�����õ�������Ϸ�е�Ψһ��һ��OpenGL�����

//CCLayer�����࣬��cocos2d-x�о��������Ϸ��
//         ��ĵط���һ�������п���װ�ض����
//         ʵ�ֶ��ײ�ͬ�����롢������߼�����
//         ����װ�볡���вſ��Ա���������

//CCScene�������࣬��cocos2d-x��ֱ�ӿ��Ա�����
//         װ�ص��࣬��������ʵ��ʲô��������
//         ��������Ϊװ�ز������
//create��static��������һ������

//CCNode�����ڵ��࣬�������㶼��CCNode�����࣬��Щ
//        ������󶼿��԰������νṹ������֯��һ��
//        ����������ͨ��CCNode�ṩ��addChild����֯
//        �ģ�һ����Ϸѭ���е��ݻ�ѳ���������һ��
//        �ȸ����������еĲ�����롢������߼���ִ
//        ��һ��
//addChild�������ӽڵ�