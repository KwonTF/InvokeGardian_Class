#include "Intro.h"

Intro::~Intro()
{
}

bool Intro::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	createGameScene();

	return true;
}

cocos2d::CCScene * Intro::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Intro *layer = Intro::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Intro::createGameScene(void)
{
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* openingImage = CCSprite::create("Background/Start_Background.png");
	openingImage->setPosition(ccp(_screenSize.width * 0.5f,_screenSize.height * 0.5f));
	this->addChild(openingImage);
	auto item_1 = MenuItemImage::create("UI/Menu_Start.png", "UI/Menu_Start.png", "UI/Menu_Start.png", CC_CALLBACK_1(Intro::menuCallback1, this));


	auto menu = Menu::create(item_1, NULL);

	menu->alignItemsVertically();
	menu->setPosition(Vec2(950,375));
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu);
}

void Intro::changeScene(void)
{
	CCScene* pScene = HelloWorld::createScene();

	CCTransitionScene* pTran = CCTransitionFade::create(0.2f, pScene);

	CCDirector::sharedDirector()->replaceScene(pTran);

}

void Intro::menuCallback1(cocos2d::Ref* pSender)
{
	changeScene();
}