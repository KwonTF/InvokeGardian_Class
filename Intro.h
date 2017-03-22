#pragma once
#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

class Intro : public cocos2d::CCLayer
{
private:
	CCSize _screenSize;

public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void changeScene(void);
	void menuCallback1(cocos2d::Ref * pSender);
	CREATE_FUNC(Intro);

	void createGameScene(void);
	~Intro();
};

#endif // __INTRO_SCENE_H__
