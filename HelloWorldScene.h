/*******************************
Invoke Gardian HelloWorldScene 파일(cpp, h)
----------------------------------
작성자: 차영철, 권태형
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
	//아래에서부터 구현
	//------------------
	//게임 씬의 구현
	void createGameScene();
	//매 시간마다 스케줄링 되는 함수들
	void onTimeUpdate(float input);
	//마우스 이벤트들
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseScroll(cocos2d::Event* event);

private:
	Player* player;
	CCSprite* statusBar;

};
//스프라이트의 앵커포인트를 가운데로 맞춰준다.
void setSpriteAnchor_Center(CCSprite *input);
#endif // __HELLOWORLD_SCENE_H__
