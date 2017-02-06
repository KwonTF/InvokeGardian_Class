/*******************************
Invoke Gardian HelloWorldScene ����(cpp, h)
----------------------------------
�ۼ���: ����ö, ������
********************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainHeader.h"
USING_NS_CC;

using namespace cocostudio::timeline;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	virtual bool init();
    CREATE_FUNC(HelloWorld);
	//------------------
	//�Ʒ��������� ����
	//------------------
	//���� ���� ����
	void createGameScene();
	//�� �ð����� �����ٸ� �Ǵ� �Լ���
	void onTimeUpdate(float input);
	//���콺 �̺�Ʈ��
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseScroll(cocos2d::Event* event);

private:
	Player* player;
	CCSprite* statusBar;

};
//��������Ʈ�� ��Ŀ����Ʈ�� ����� �����ش�.
void setSpriteAnchor_Center(CCSprite *input);
#endif // __HELLOWORLD_SCENE_H__
