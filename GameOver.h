#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Intro.h"

using namespace cocos2d;

class GameOver : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void changeScene(void);
	CREATE_FUNC(GameOver);

	void createGameScene(void);
	void menuCallback1(cocos2d::Ref * pSender);
	void menuCallback2(cocos2d::Ref * pSender);
	~GameOver();
private:
	CCSize _screenSize;
};

#endif // __GAMEOVER_SCENE_H__