#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainHeader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size GameSize = Size::Size(960, 640);
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

	return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand(time(NULL));

    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);

	// set contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	// Set MouseEvent
	auto Mouse = EventListenerMouse::create();
	mouse = Vec2(0, 0);
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
	layerMissile->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	layerMissile->setPosition(Vec2());
	this->addChild(layerMissile);

	createGameScene();
	initGameVariable();
	makeTower();

#ifdef __DEBUG_GAME_VARIABLE__
	setMonsterAmountViewer();
#endif // __DEBUG_GAME_VARIABLE__
	
	this->schedule(schedule_selector(HelloWorld::onTimeUpdate));
	this->schedule(schedule_selector(HelloWorld::gameTimer), 1.0f);

    return true;
}

// 부딪힘 인식
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto sp1 = (Collisioner*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Collisioner*)contact.getShapeB()->getBody()->getNode();
	sp1->collisioned(sp2->getAttack(), sp2->getCondition());
	sp2->collisioned(sp1->getAttack(), sp1->getCondition());
	
	return true;
}

void HelloWorld::createGameScene()//권태형 제작
{
	Size _winSize = Director::sharedDirector()->getWinSize();
	player = Player::createAndInit();
	statusBar = Sprite::create("UI/MainStatusBar.png");
	statusBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//setSpriteAnchor_Center(statusBar);
	player->setPosition(_winSize.width / 2 - 200, _winSize.height / 2 - 200);
	statusBar->setPosition(_winSize.width / 2, _winSize.height * 1 / 20);
	ttf1 = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);

	roundViewer = LabelTTF::create("Round", "fonts/RoundGothic.ttf", 30);
	roundViewer->setPosition(480, 600);
	roundViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(roundViewer);

	timeViewer = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	timeViewer->setPosition(480, 550);
	timeViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(timeViewer);
}

/*
게임 내 변수 초기화 함수
변수 목록 : 
create by ZeroFe
*/
void HelloWorld::initGameVariable()
{
	roundNum = 1;

	gameTime = ROUNDTIME;
	isRound = true;
	roundViewer->setString("Round");
	timeViewer->setString(std::to_string(gameTime));

	mutateBasePer = 1;

	monsterBaseAmount = 16;
	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
}

#ifdef __DEBUG_GAME_VARIABLE__
void HelloWorld::setMonsterAmountViewer()
{
	monsterAmountViewer = LabelTTF::create("Num", "fonts/RoundGothic.ttf", 30);
	monsterAmountViewer->setPosition(900, 600);
	monsterAmountViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(monsterAmountViewer);
}
#endif // __DEBUG_GAME_VARIABLE__

void HelloWorld::makeTower()
{
	tower = Tower::create("Unit/Hostile.png");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);
	auto body = PhysicsBody::createBox(tower->getContentSize(), material);
	tower->setPhysicsBody(body);

	tower->getPhysicsBody()->setCategoryBitmask(0x003);
	tower->getPhysicsBody()->setContactTestBitmask(0xC30);
	tower->getPhysicsBody()->setCollisionBitmask(0x030);

	tower->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tower->setPosition(Vec2(480, 320));

	tower->setTowerBase();

	// hpBar 넣을 것

	layerMissile->addChild(tower);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	Vec2 playerPos = player->getPosition();
	//각도 구하기
	diffUnitVec2 = mouse - playerPos;
	diffUnitVec2 = diffUnitVec2.getNormalized();

	//cocos2d::log("%f", cursorAngle);
	player->setRotation(90 - diffUnitVec2.getAngle() * 180 / M_PI);
}

void HelloWorld::gameTimer(float dt)
{
	// 라운드/셋업 변환 부분
	if (gameTime <= 0)
	{
		if (isRound != 0)
		{
			roundNum++;
			isRound = true;
			gameTime = ROUNDTIME;
			//roundChange();
		}
		else
		{
			isRound = false;
			gameTime = SETUPTIME;
		}
	}

	// 시간 감소 부분
	gameTime--;
	timeViewer->setString(std::to_string(gameTime));

	// 몬스터 생성 부분(임시)
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
	mousePosition.y = 640 - mousePosition.y;
	player->gotoPoint(mousePosition, calculateDegree(player->getPosition(), mousePosition));
	auto monster = makeMonster();
	monster->setRange(50);
	monster->setSpeed(10);
	monster->setEnemyAim(tower->getPosition());
	addChild(monster);
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

/*
Round가 바뀔 때 변수들을 다시 초기화하는 함수
create by ZeroFe
*/
void HelloWorld::roundChange()
{
	roundNum++;

	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
}

// 실험용 몬스터 생성
// create by ZeroFe
Enemy* HelloWorld::makeMonster()
{
	Enemy* monster = Enemy::create("Unit/Hostile.png");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createBox(monster->getContentSize(), material);

	monster->setPhysicsBody(body);
	monster->setEnemyTeam();
	monster->setPosition(Vec2(800 * (rand() % 2), rand() % 600));

	monster->setHP(10);
	monster->setHPRegen(1);
	monster->setAttack(5);
	// monster->schedule(schedule_selector(Unit::regeneration), 1.0f);

	cocos2d::log("monster make : %d %d", monster->getHP(), monster->getAttack());

	return monster;
}

Missile* HelloWorld::makeMissile()
{
	Missile* missile = Missile::create("Others/Bullet.PNG");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(missile->getContentSize().width / 2, material);

	// 몸체 설정
	missile->setPhysicsBody(body);
	missile->setPosition(player->getPosition());
	missile->getPhysicsBody()->setVelocity(Vec2(0, missile->getSpeed()));

	// 내부 값 설정
	missile->setAttack(3);
	missile->setSpeed(300.0);
	missile->setPenetCount(1);
	missile->setRange(600);

	return missile;
}

void HelloWorld::fireMissile()
{
	// BulletObj로 만든거
	/*
	BulletObj * missile = BulletObj::createAndInit(player->getRotation());
	missile->setPosition(player->getPosition());
	missile->setRotation(player->getRotation());
	layerMissile->addChild(missile);
	*/

	// Missile로 만든거
	auto bullet = HelloWorld::makeMissile();
	Vec2 missileSpeed = diffUnitVec2;
	missileSpeed.scale(400.0);
	bullet->getPhysicsBody()->setVelocity(missileSpeed);
	
	bullet->setMissileTeam(0);

	layerMissile->addChild(bullet);
}

void setSpriteAnchor_Center(Sprite * input)//권태형 제작
{
	input->setAnchorPoint(Vec2(0.5, 0.5));
}

float calculateDegree(Vec2 current, Vec2 point)
{
	Vec2 tempVec = point - current;
	tempVec = tempVec.getNormalized();
	return tempVec.getAngle()* 180 / M_PI;
}
