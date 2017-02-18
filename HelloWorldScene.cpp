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

	return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
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
	layerEnemy = Layer::create();
	layerMissile->setAnchorPoint(Vec2(1, 1));
	layerMissile->setPosition(Vec2());
	layerEnemy->setAnchorPoint(AnchorCenter);
	layerEnemy->setPosition(Vec2());
	this->addChild(layerMissile);
	this->addChild(layerEnemy);
	createGameScene();
	initGameVariable();
	
	this->schedule(schedule_selector(HelloWorld::onTimeUpdate));
	this->schedule(schedule_selector(HelloWorld::gameTimer), 1.0f);

    return true;
}

// 부딪힘 인식
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto sp1 = (Collisioner*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Collisioner*)contact.getShapeB()->getBody()->getNode();
	int tag1 = sp1->getTag();
	int tag2 = sp2->getTag();
	sp1->collisioned(sp2->getAttack(), sp2->getCondition());
	sp2->collisioned(sp1->getAttack(), sp1->getCondition());
	//log("%d : %d  %d : %d", tag1, sp1->getHP(), tag2, sp2->getHP());
	
	return true;
}

void HelloWorld::createGameScene()//권태형 제작
{
	CCSize _winSize = CCDirector::sharedDirector()->getWinSize();
	player = Player::createAndInit();
	statusBar = CCSprite::create("UI/MainStatusBar.png");
	basement = Basement::createAndInit();
	setSpriteAnchor_Center(statusBar);
	basement->setAnchorPoint(AnchorCenter);
	basement->setPosition(_winSize.width / 2, _winSize.height / 2);
	player->setPosition(_winSize.width / 2 - 200, _winSize.height / 2 - 200);
	statusBar->setPosition(_winSize.width / 2, _winSize.height * 1 / 20);
	ttf1 = CCLabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(AnchorCenter);
	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);
	this->addChild(basement);

	roundViewer = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	roundViewer->setPosition(480, 600);
	roundViewer->setAnchorPoint(AnchorCenter);
	this->addChild(roundViewer);

	timeViewer = LabelTTF::create("Default", "fonts/RoundGothic.ttf", 30);
	timeViewer->setPosition(480, 550);
	timeViewer->setAnchorPoint(AnchorCenter);
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
	roundViewer->setString("Round: " + std::to_string(roundNum));
	timeViewer->setString(std::to_string(gameTime));

	mutateBasePer = 1;
	monsterBaseAmount = 16;
	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;

	std::list<Vec2> positonTemp;
	for (int i = 0; i < monsterRoundAmount; i++) {
		positonTemp.push_back(Vec2(rand() % 2, rand() % 640));
	}
	while (positonTemp.size() != 0) {
		createEnemy(positonTemp.front());
		positonTemp.pop_front();
	}
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	Vec2 playerPos = player->getPosition();
	cursorAngle = calculateDegree(playerPos, mouse);
	//cocos2d::log("%f", cursorAngle);
	player->setRotation(90 - cursorAngle);
	//BulletObj 충돌판정
	for (int i = 0; i < missileArray.size(); i++) {
		//총알이 화면을 벗어날시 삭제
		/*if(missileArray.at(i)->getPositionX() < 0 || missileArray.at(i)->getPositionX() > 960|| missileArray.at(i)->getPositionY()<0 || missileArray.at(i)->getPositionY()>640){
			layerMissile->removeChild(missileArray.at(i));
			missileArray.eraseObject(missileArray.at(i));
			ttf1->setString("Deleted");
		}
		else {*/
			Rect bulletarea = missileArray.at(i)->getBoundingBox();
			for (int j = 0; j < enemyArray.size(); j++) {
				Rect hostilearea = enemyArray.at(j)->getBoundingBox();
				//충돌시 처리
				if (hostilearea.intersectsRect(bulletarea)) {
					enemyArray.at(j)->setHP(enemyArray.at(j)->getHP() - 50);
					if (enemyArray.at(j)->getHP() <= 0) {
						ttf1->setString("Kill");
						layerEnemy->removeChild(enemyArray.at(j));
						enemyArray.eraseObject(enemyArray.at(j));
					}
					layerMissile->removeChild(missileArray.at(i));
					missileArray.eraseObject(missileArray.at(i));
					break;
				}
			}
		// }
	}
	if (basement->getHP() == 0) {
		basement->setOpacity(0);
		roundViewer->setString("GameOver");
	}
	if (enemyArray.size() == 0) {
		roundViewer->setString("Stage Clear!");
	}
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

	// 몬스터 생성 부분(임시)
	cocos2d::log("gameTimer");
	timeViewer->setString(std::to_string(gameTime));
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
	player->gotoPoint(mousePosition, calculateDegree(player->getPosition(),mousePosition));
	//auto monster = makeMonster();
	//addChild(monster);
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
Unit* HelloWorld::makeMonster()
{
	Unit* monster = Unit::create("Unit/Hostile.png");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(monster->getContentSize().width / 2, material);

	monster->setPhysicsBody(body);

	monster->getPhysicsBody()->setCategoryBitmask(0x0C0);
	monster->getPhysicsBody()->setContactTestBitmask(0x30C);
	monster->getPhysicsBody()->setCollisionBitmask(0x00C);

	monster->setPosition(Vec2(800, rand() % 600));
	monster->setTag(10);

	monster->setHP(10);
	monster->setAttack(5);

	return monster;
}

/*Missile* HelloWorld::makeMissile()
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
*/
void HelloWorld::fireMissile()
{
	// BulletObj로 만든거.
	BulletObj * bullet = BulletObj::createAndInit(player->getRotation());
	bullet->setPosition(player->getPosition());
	bullet->setRotation(player->getRotation());
	layerMissile->addChild(bullet);
	missileArray.pushBack(bullet);
	//BulletObj * missile = BulletObj::createAndInit(player->getRotation());
	// Missile로 만든거
	/*auto missile = HelloWorld::makeMissile();
	missile->getPhysicsBody()->setVelocity(Vec2(400 * cos(cursorAngle * M_PI / 180), 400 * sin(cursorAngle * M_PI / 180)));
	
	missile->setMissileTeam(0);

	layerMissile->addChild(missile);*/
}

void HelloWorld::createEnemy(Vec2 position)
{
	Enemy* enemy = Enemy::createAndInit();
	if (position.x == 0) {
		enemy->setPositionX(0);
	}
	else {
		enemy->setPositionX(960);
	}
	enemy->setPositionY(position.y);
	enemy->setAnchorPoint(AnchorCenter);
	enemy->setTarget(basement);
	layerEnemy->addChild(enemy);
	enemyArray.pushBack(enemy);
}

void setSpriteAnchor_Center(CCSprite * input)//권태형 제작
{
	input->setAnchorPoint(Vec2(0.5, 0.5));
}

float calculateDegree(Vec2 current, Vec2 point)
{
	float diffX = point.x - current.x;
	float diffY = point.y - current.y;
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle);
	return angle;
}