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

//CCNode��cocos2d-x�еĺ����࣬����������֯�������ģ���
//������λ�á��ߴ硢ê��Ⱥ��ĳ�Ա���ݣ���Щ������ϵ��
//��������Ļ��ƣ�CCNode����һ��draw�����������������
//���������о����CCNode������Ը����Լ����������д��
//���������糡����û����д�ú����������о���д�˸ú���
//�������������һ��ͼ�񣬶����������Ļ��ƾ����ȸ�����
//���CCNode�������ε���ÿ���ڵ��draw����

//getContentSize���õ��ߴ�
//setContentSize�����óߴ�
//CCNode��ҿ��Խ�������Ϊһ����Ļ���Σ�����
//�Ŀ�߾������ĳߴ����

//getPosition���õ�λ��
//setPosition������λ��
//CCNode��λ������Ҫ��ϸ��ڵ㣨��ȻҲ��һ��
//CCNode����ԭ���Լ���ǰ�ڵ��ê�㹲ͬ���õ�
//��Ҳ����˵���λ��������ڸ��ڵ��ԭ�����
//�ģ������ڻ��Ƶ�ʱ�򣬵�ǰCCNode�������ȥ
//�Զ˵�ǰ�������λ��

//getAnchorPoint���õ�ê��
//setAnchorPoint������ê��
//ignoreAnchorPointForPosition���Ƿ����ê��
//isIgnoreAnchorPointForPosition���õ��Ƿ����ê��
//ê����ÿ��CCNode�е�һ���㣨�������������Ϊ
//0~1֮��ı���ֵ������0.5��0.5�ͱ�ʾλ������
//���CCNode�����м䣩��ê������þ������λ��
//���л��ƣ��������ê�㣬��ôê�����(0,0)