#include "GameOver.h"

bool GameOver::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	createGameScene();

	return true;
}

cocos2d::CCScene * GameOver::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	GameOver *layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameOver::changeScene(void)
{
	Scene* pScene = Intro::scene();

	TransitionScene* pTran = TransitionFade::create(0.2f, pScene);

	Director::sharedDirector()->replaceScene(pTran);
}

void GameOver::createGameScene(void)
{
	_screenSize = Director::sharedDirector()->getWinSize();

	CCSprite* openingImage = Sprite::create("Background/GameOver_Background.png");
	openingImage->setPosition(Vec2(_screenSize.width, _screenSize.height) * 0.5f);
	this->addChild(openingImage);
	auto item_1 = MenuItemImage::create("UI/GameOver_Menu.png", "UI/GameOver_Menu.png", "UI/GameOver_Menu.png", CC_CALLBACK_1(GameOver::menuCallback1, this));
	auto item_2 = MenuItemImage::create("UI/GameOver_Exit.png", "UI/GameOver_Exit.png", "UI/GameOver_Exit.png", CC_CALLBACK_1(GameOver::menuCallback2, this));


	auto menu = Menu::create(item_1, item_2, NULL);

	menu->alignItemsVertically();
	menu->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.3f));
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu);
}

void GameOver::menuCallback1(cocos2d::Ref * pSender)
{
	changeScene();
}

void GameOver::menuCallback2(cocos2d::Ref * pSender)
{
	CCDirector::sharedDirector()->end();
}

GameOver::~GameOver()
{
}


