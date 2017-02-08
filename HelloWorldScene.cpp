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
	mouse = Point(0, 0);
	Mouse->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	Mouse->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	Mouse->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	Mouse->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);
	//Set KeyBoard Event
	auto keyBoard = EventListenerKeyboard::create();
	keyBoard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyBoard->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoard, this);
	//미사일 레이어들 젹용
	layerMissile = Layer::create();
	layerMissile->setAnchorPoint(Vec2(1, 1));
	layerMissile->setPosition(Vec2());
	this->addChild(layerMissile);
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
	ttf1 = CCLabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(CCPoint(0.5, 0.5));
	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	float angle = calculateDegree(Point(player->getPositionX(), player->getPositionY()), mouse);
	player->setRotation(angle);
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
}

void HelloWorld::onMouseUp(cocos2d::Event * event)
{
}

void HelloWorld::onMouseMove(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	mouse = Point(mousePosition.x, mousePosition.y);
}

void HelloWorld::onMouseScroll(cocos2d::Event * event)
{
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE :
		fireMissile();
		break;
	default:
		break;
	}
}

void HelloWorld::fireMissile()
{
	BulletObj * missile = BulletObj::createAndInit(player->getRotation() + 45);
	missile->setPosition(player->getPosition());
	missile->setRotation(player->getRotation());
	layerMissile->addChild(missile);
}

void setSpriteAnchor_Center(CCSprite * input)//권태형 제작
{
	input->setAnchorPoint(Vec2(0.5, 0.5));
}

float calculateDegree(Point & current, Point & point)
{
	float diffX = point.x - current.x;
	float diffY = point.y - current.y;
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle);
	return angle;
}
