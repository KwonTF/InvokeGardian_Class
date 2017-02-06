#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	// Set MouseEvent
	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	Mouse->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	Mouse->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	Mouse->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);
	createGameScene();
	this->schedule(schedule_selector(HelloWorld::onTimeUpdate));
    return true;
}

void HelloWorld::createGameScene()//권태형 제작
{
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
	player = Player::createAndInit();
	statusBar = CCSprite::create("UI/MainStatusBar.png");
	setSpriteAnchor_Center(statusBar);
	player->setPosition(_winSize.width / 2 -200, _winSize.height / 2 -200);
	statusBar->setPosition(_winSize.width / 2, _winSize.height * 1 / 20);
	this->addChild(player);
	this->addChild(statusBar);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	player->gotoPoint(mousePosition.x, mousePosition.y);
}

void HelloWorld::onMouseUp(cocos2d::Event * event)
{
}

void HelloWorld::onMouseMove(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	float diffX = mousePosition.x - player->getPositionX();
	float diffY = mousePosition.y - player->getPositionY();
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle) + 45;
	player->setRotation(angle);
}

void HelloWorld::onMouseScroll(cocos2d::Event * event)
{
}

void setSpriteAnchor_Center(CCSprite * input)//권태형 제작
{
	input->setAnchorPoint(Vec2(0.5, 0.5));
}
