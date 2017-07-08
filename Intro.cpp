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

cocos2d::Scene * Intro::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	Intro *layer = Intro::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Intro::createGameScene(void)
{
	_screenSize = Director::sharedDirector()->getWinSize();

	Sprite* openingImage = Sprite::create("Background/Start_Background.png");
	openingImage->setPosition(ccp(_screenSize.width * 0.5f,_screenSize.height * 0.5f));
	this->addChild(openingImage);
	auto item_1 = MenuItemImage::create("UI/Menu_Start.png", "UI/Menu_Start.png", "UI/Menu_Start.png", CC_CALLBACK_1(Intro::menuCallback1, this));
	auto item_2= MenuItemImage::create("UI/Menu_Play.png", "UI/Menu_Play.png", "UI/Menu_Play.png", CC_CALLBACK_1(Intro::menuCallback2, this));
	auto item_3 = MenuItemImage::create("UI/Menu_Exit.png", "UI/Menu_Exit.png", "UI/Menu_Exit.png", CC_CALLBACK_1(Intro::menuCallback3, this));
	
	auto item_4 = MenuItemImage::create("UI/Menu_Debug.png", "UI/Menu_Debug.png", "UI/Menu_Debug.png", CC_CALLBACK_1(Intro::menuCallback1, this));
	auto DebugMenu = Menu::create(item_4, nullptr);
	DebugMenu ->setPosition(_screenSize.width * 0.9f, _screenSize.height*0.9f);
	this->addChild(DebugMenu);

	auto menu = Menu::create(item_1, item_2, item_3, nullptr);
	
	menu->alignItemsVertically();
	menu->setPosition(Vec2(1000,270));
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(menu);

	Play = Sprite::create("UI/HowtoPlay.png");
	Play->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Play->setPosition(Vec2(430, 270));
	playVisible = false;
	Play->setVisible(playVisible);
	this->addChild(Play);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/enchanted.wav", true);
}

void Intro::changeScene(Ref* item)
{
	Scene* pScene = HelloWorld::createScene(item->_ID);
	TransitionScene* pTran = TransitionFade::create(0.2f, pScene);
	Director::sharedDirector()->replaceScene(pTran);

}

void Intro::menuCallback1(cocos2d::Ref* pSender)
{
	changeScene(pSender);
}

void Intro::menuCallback2(cocos2d::Ref* pSender)
{
	if (playVisible)
		playVisible = false;
	else
		playVisible = true;
	Play->setVisible(playVisible);
}

void Intro::menuCallback3(cocos2d::Ref* pSender)
{
	Director::sharedDirector()->end();
}