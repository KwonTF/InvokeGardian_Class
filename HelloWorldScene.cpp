#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainHeader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size GameSize = Size::Size(540, 960);
	Vec2 gravity = Vec2(0.0f, 0.0f);

	// make scene with physics
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);			// draw 
	scene->getPhysicsWorld()->setGravity(gravity);

	// make physics body
	auto body = PhysicsBody::createEdgeBox(GameSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	auto layer = HelloWorld::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	// set contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

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

	//미사일 레이어들?
	layerMissile = Layer::create();
	layerMissile->setAnchorPoint(Vec2(1, 1));
	layerMissile->setPosition(Vec2());
	this->addChild(layerMissile);
	createGameScene();
	this->schedule(schedule_selector(HelloWorld::onTimeUpdate));

    return true;
}

// 부딪힘 인식
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto sp1 = (Collisioner*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Collisioner*)contact.getShapeB()->getBody()->getNode();
	int tag1 = sp1->getTag();
	int tag2 = sp2->getTag();
	sp1->getDamage(sp2->getAttack());
	sp2->getDamage(sp1->getAttack());
	sp1->getCondition();
	sp2->getCondition();
	//log("%d : %d  %d : %d", tag1, sp1->getHP(), tag2, sp2->getHP());
	
	return true;
}

void HelloWorld::createGameScene()//권태형 제작
{
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
	player = Player::createAndInit();
	statusBar = CCSprite::create("UI/MainStatusBar.png");
	setSpriteAnchor_Center(statusBar);
	player->setPosition(_winSize.width / 2 - 200, _winSize.height / 2 - 200);
	statusBar->setPosition(_winSize.width / 2, _winSize.height * 1 / 20);
	ttf1 = CCLabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(AnchorCenter);
	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	Vec2 playerPos = player->getPosition();
	float angle = calculateDegree(playerPos, mouse);
	player->setRotation(90 - angle);
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
}

void HelloWorld::onMouseMove(cocos2d::Event * event)
{
	EventMouse *e = (EventMouse*)event;
	//auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	mouse = Point(e->getCursorX(), e->getCursorY());
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		fireMissile();
		break;
	default:
		break;
	}
}

void HelloWorld::fireMissile()
{
	BulletObj * missile = BulletObj::createAndInit(player->getRotation());
	missile->setPosition(player->getPosition());
	missile->setRotation(player->getRotation());
	layerMissile->addChild(missile);
}

void setSpriteAnchor_Center(CCSprite * input)//권태형 제작
{
	input->setAnchorPoint(Vec2(0.5, 0.5));
}

float calculateDegree(Vec2 & current, Vec2 & point)
{
	float diffX = point.x - current.x;
	float diffY = point.y - current.y;
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle);
	return angle;
}