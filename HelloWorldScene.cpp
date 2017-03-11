#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainHeader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 gravity = Vec2(0.0f, 0.0f);

	// make scene with physics
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);			// draw 
	scene->getPhysicsWorld()->setGravity(gravity);

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
	divisonNum = 1;
	MP = 100;
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
	_winSize = Director::sharedDirector()->getWinSize();
	player = Player::createAndInit();
	statusBar = Sprite::create("UI/MainStatusBar.png");
	statusBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mpSprite = Sprite::create("UI/MpStatusBar.png");
	mpBar = CCProgressTimer::create(mpSprite);
	mpBar->setType(kCCProgressTimerTypeBar);
	mpBar->setPercentage(MP);
	mpBar->setMidpoint(ccp(0, 0.5f));
	mpBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	mpBar->setBarChangeRate(Vec2(1, 0));
	setSpriteAnchor_Center(statusBar);
	player->setPosition(_winSize.width / 2 - 200, _winSize.height / 2 - 200);
	statusBar->setPosition(_winSize.width / 2, _winSize.height * 1 / 20);
	mpBar->setPosition(_winSize.width / 2 + 267, _winSize.height * 1 / 20 - 25);
	mpState = LabelTTF::create("100/100", "fonts/RoundGothic.ttf", 30);
	mpState->setColor(Color3B(0, 100, 250));
	mpState->setPosition(_winSize.width / 2 + 267, _winSize.height * 1 / 20 - 25);
	ttf1 = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);
	this->addChild(mpBar);
	this->addChild(mpState);

	roundViewer = LabelTTF::create("Round", "fonts/RoundGothic.ttf", 30);
	roundViewer->setColor(Color3B::RED);
	roundViewer->setPosition(_winSize.width / 2, _winSize.height - 100);
	roundViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(roundViewer);

	timeViewer = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	timeViewer->setColor(Color3B::RED);
	timeViewer->setPosition(_winSize.width / 2, _winSize.height - 150);
	timeViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(timeViewer);
	this->schedule(schedule_selector(HelloWorld::mpRestore), 0.5f);
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
	canUpgrade = false;

	roundViewer->setString("Round");
	timeViewer->setString(std::to_string(gameTime));

	// 변형 확률
	mutateBasePer = 1;
	mutateRoundBonus = 2;

	// 나오는 몬스터 수
	monsterBaseAmount = 16;
	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
	monsterPresentAmount = 0;
}

#ifdef __DEBUG_GAME_VARIABLE__
void HelloWorld::setMonsterAmountViewer()
{
	monsterAmountViewer = LabelTTF::create("Num", "fonts/RoundGothic.ttf", 30);
	monsterAmountViewer->setPosition(_winSize.width - 200 , _winSize.height - 150);
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
	tower->getPhysicsBody()->setDynamic(false);
	tower->getPhysicsBody()->setCategoryBitmask(0x003);
	tower->getPhysicsBody()->setContactTestBitmask(0xC30);
	tower->getPhysicsBody()->setCollisionBitmask(0x030);

	tower->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tower->setPosition(Vec2(_winSize.width / 2, _winSize.height/2));

	// hpBar 넣을 것

	layerMissile->addChild(tower);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	Vec2 playerPos = player->getPosition();
	//각도 구하기
	diffUnitVec2 = mouse - playerPos;
	diffUnitVec3 = diffUnitVec2;
	diffUnitVec2 = diffUnitVec2.getNormalized();
	//cocos2d::log("%f", cursorAngle);
	player->setRotation(90 - diffUnitVec2.getAngle() * 180 / M_PI);
	mpBar->setPercentage(MP);
	std::string mpText = std::to_string(static_cast<int>(ceil(MP))) + " / 100";
	mpState->setString(mpText);
}

/*
매 초마다 계산하는 타이머
게임 시간 흐름에 사용
*/
void HelloWorld::gameTimer(float dt)
{
	// 라운드/셋업 변환 부분
	if (gameTime <= 0)
	{
		if (isRound == false)
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
			roundViewer->setString("Set Up");
		}
	}

	// 시간 감소 부분
	gameTime--;
	timeViewer->setString(std::to_string(gameTime));

	// 몬스터 생성 부분(임시)
	if (monsterRoundAmount > 0)
	{
		monsterRoundAmount--;
		auto monster = makeMonster();
		monster->setBaseAbillity(GameData::roundEnemyHP[roundNum], GameData::roundEnemyAttack[roundNum],
			GameData::enemyAttackRange, GameData::enemyMoveSpeed, GameData::enemyAttackSpeed);
		monster->setEnemyAim(tower->getPosition());
		monster->setDeathCallback(CC_CALLBACK_0(HelloWorld::monsterDeath, this));
		monster->setExplodeCallback(CC_CALLBACK_0(HelloWorld::explodeEffect, this, monster->getPosition()));
		enemyVector.pushBack(monster);
		addChild(monster);
		monsterPresentAmount++;
	}
			// 몬스터 확인용
	#ifdef __DEBUG_GAME_VARIABLE__
	monsterAmountViewer->setString(std::to_string(monsterPresentAmount));
	#endif // __DEBUG_GAME_VARIABLE__
}

void HelloWorld::mpRestore(float input)
{
	if (MP < 100) {
		MP++;
	}
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
	mousePosition.y = 640 - mousePosition.y;
	player->gotoPoint(mousePosition, calculateDegree(player->getPosition(), mousePosition));
}

void HelloWorld::onMouseMove(cocos2d::Event * event)
{
	EventMouse *e = (EventMouse*)event;
	//auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	mouse = Point(e->getCursorX(), e->getCursorY());
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	int temp = tempVector.size();
	int tempMP = MP;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		switch (temp)
		{
		case 1:
			tempMP -= 10;
			break;
		case 2:
			tempMP -= 15;
			break;
		case 3:
			tempMP -= 23;
			break;
		case 4:
			tempMP -= 35;
			break;
		case 5:
			tempMP -= 55;
			break;
		case 6:
			tempMP -= 80;
			break;
		case 0:
			tempMP -= 2;
			break;
		default:
			tempMP -= 101;
			break;
		}
		if (tempMP >= 0) {
			fireMissile();
			tempVector.clear();
			divisonNum = 1;
			MP = tempMP;
		}
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		tempVector.push_back(new Knock());
		break;
	case EventKeyboard::KeyCode::KEY_W:
		tempVector.push_back(new PowerUp());
		break;
	case EventKeyboard::KeyCode::KEY_E:
		tempVector.push_back(new Explode());
		break;
	case EventKeyboard::KeyCode::KEY_A:
		tempVector.push_back(new Division());
		divisonNum+=tempVector.back()->castEffect(divisonNum);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		tempVector.push_back(new Slow());
		break;
	case EventKeyboard::KeyCode::KEY_D:
		tempVector.push_back(new Mine());
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
	// 라운드 관련 변수 변경
	roundNum++;

	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
	mutateRoundPer = mutateBasePer + mutateRoundBonus * roundNum;

	// 업그레이드 불가능 상태로 만들기
	canUpgrade = false;
	roundViewer->setColor(Color3B::RED);
	timeViewer->setColor(Color3B::RED);
}

void HelloWorld::monsterDeath()
{
	monsterPresentAmount--;
	#ifdef __DEBUG_GAME_VARIABLE__
		monsterAmountViewer->setString(std::to_string(monsterPresentAmount));
	#endif // __DEBUG_GAME_VARIABLE__
	// 라운드 변경
  	if (monsterRoundAmount <= 0 && monsterPresentAmount <= 0)
	{
		// 적용함수 만들 것
		// 남은 시간 1초 남기고 없애기
		int extraTime = gameTime - 1;
		gameTime = gameTime - extraTime;
		// 남은 시간만큼 마나 / 타워 체력 회복
		// (체력 회복은 체젠에 기반하여)

		// 업그레이드 가능 상태로 만들기
		canUpgrade = true;
  		roundViewer->setColor(Color3B::GREEN);
		timeViewer->setColor(Color3B::GREEN);
		enemyVector.clear();
	}
}

void HelloWorld::explodeEffect(Vec2 point)
{
	for (int i = 0; i < enemyVector.size(); i++) {
		if (enemyVector.at(i)->isInRange(point, 200)) {
			enemyVector.at(i)->takenDamage(100);
		}
	}
}

// 실험용 몬스터 생성
// create by ZeroFe
Enemy* HelloWorld::makeMonster()
{
	Enemy* monster = Enemy::create("Unit/Hostile0.png");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createBox(monster->getContentSize(), material);

	monster->setPhysicsBody(body);
	monster->getPhysicsBody()->setDynamic(false);
	monster->setEnemyTeam();
	monster->setPosition(Vec2(_winSize.width * (rand() % 2), (rand() % 720)));
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

	// 내부 값 설정
	missile->setAttack(10);
	missile->setSpeed(400.0);
	missile->setRange(200);
	missile->setPenetCount(1);
	return missile;
}

void HelloWorld::fireMissile()
{
	// Missile로 만든거
	for (int i = 0; i < divisonNum; i++) {
		auto missile = HelloWorld::makeMissile();
		Vec2 tempVec = diffUnitVec3;
		if (divisonNum > 1) {
			tempVec.x += random() % 100 - 50;
			tempVec.y += random() % 100 - 50;
		}
		tempVec = tempVec.getNormalized();
		missile->getPhysicsBody()->setVelocity(tempVec * missile->getSpeed());
		missile->setMissileTeam(0);
		missile->setCondition(tempVector);
		missile->castEffect();
		layerMissile->addChild(missile);
	}
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
