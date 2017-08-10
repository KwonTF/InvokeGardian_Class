#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainHeader.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene(int input)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 gravity = Vec2(0.0f, 0.0f);

	// make scene with physics
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);			// draw 
	scene->getPhysicsWorld()->setGravity(gravity);

	auto layer = HelloWorld::create();
	layer->setDebugID(input);
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

	_winSize = Director::sharedDirector()->getWinSize();
	// set contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	// set TouchesEvent
	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Set MouseEvent
	auto Mouse = EventListenerMouse::create();
	mouse = Vec2::ZERO;
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

	//배경 지정
	Background = Sprite::create("Background/Background.png");
	Background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Background->setPosition(_winSize.width / 2, _winSize.height / 2);
	this->addChild(Background);

	//배경음 적용
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM/NomalPlay_Full_MixDown.wav", true);

	//미사일 레이어들?
	layerMissile = Layer::create();
	layerMissile->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	layerMissile->setPosition(Vec2());
	this->addChild(layerMissile);

	initGameVariable();
	createGameScene();
	makeTower();
	setMonsterAmountViewer();
	setDebugMode();

	// 스케쥴 설정
	this->schedule(schedule_selector(HelloWorld::onTimeUpdate));
	this->schedule(schedule_selector(HelloWorld::gameTimer), 1.0f);
	this->schedule(schedule_selector(HelloWorld::mpRestore));
	this->schedule(schedule_selector(HelloWorld::monsterCreateTimer));

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

// raycast 용
void HelloWorld::onTouchesEnded(const std::vector<Touch*> &touches, Event* event)
{
	for (auto &touch : touches)
	{

	}
}

void HelloWorld::createGameScene()//권태형 제작
{
	player = Player::createAndInit();
	player->setPosition(_winSize.width / 2 - 200, _winSize.height / 2 - 200);
	player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	UISetting();
}

/*
게임 내 변수 초기화 함수
변수 목록 : 
create by ZeroFe
*/
void HelloWorld::initGameVariable()
{
	divisonNum = 1;

	MPCurrent = 100;
	MPMax = 100;
	MPRegenCount = 0;
	MPRegenAmount = 3;

	SlotLevel = 2;

	roundNum = 1;

	gameTime = ROUNDTIME;
	isRound = true;
	canUpgrade = false;

	setRoundVariable();
}

void HelloWorld::setMonsterAmountViewer()
{
	monsterPresentViewer = Label::create("Num", fontPath, 30);
	monsterPresentViewer->setPosition(_winSize.width - 30 , _winSize.height - 20);
	monsterPresentViewer->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	this->addChild(monsterPresentViewer);

	monsterExistViewer = Label::create("Num", fontPath, 30);
	monsterExistViewer->setPosition(_winSize.width - 30, _winSize.height - 60);
	monsterExistViewer->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	this->addChild(monsterExistViewer);
}

void HelloWorld::UISetting()
{
	mpSprite = Sprite::create("UI/MPStatusBar.png");
	mpBar = CCProgressTimer::create(mpSprite);
	mpBar->setType(kCCProgressTimerTypeBar);
	mpBar->setPercentage(persent(100, 100));
	mpBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT);
	mpBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mpBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);

	hpSprite = Sprite::create("UI/HPStatusBar.png");
	hpBar = CCProgressTimer::create(hpSprite);
	hpBar->setType(kCCProgressTimerTypeBar);
	hpBar->setPercentage(persent(500, 500));
	hpBar->setMidpoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	hpBar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	hpBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);

	statusBar = Sprite::create("UI/MainStatusBar.png");
	statusBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	statusBar->setPosition(_winSize.width / 2, 0);

	Sprite* slotBack = Sprite::create("UI/SlotBack.png");
	slotBack->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	slotBack->setPosition(_winSize.width / 2, 40);
	// for UI check
	popback = Sprite::create("UI/PopBack.png");
	popback->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	popback->setPosition(-300, _winSize.height / 2);
	this->addChild(popback);
	pop1 = Sprite::create("UI/Popup_1.png");
	pop1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	pop1->setPosition(-300, _winSize.height / 2);
	this->addChild(pop1);
	pop2 = Sprite::create("UI/Popup_2.png");
	pop2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	pop2->setPosition(-300, _winSize.height / 2);
	this->addChild(pop2);
	pop3 = Sprite::create("UI/Popup_3.png");
	pop3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	pop3->setPosition(-300, _winSize.height / 2);
	this->addChild(pop3);
	popbutton = Sprite::create("UI/PopButton.png");
	popbutton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	popbutton->setPosition(0, _winSize.height / 2);
	popbutton->setRotation(0);
	popbutton->setOpacity(0);
	this->addChild(popbutton);

	mpBar->setPosition(_winSize.width / 2, 0);
	mpState = Label::createWithTTF("100/100", fontPath, 30);
	mpState->setColor(Color3B(0, 100, 255));
	mpState->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	mpState->setPosition(_winSize.width / 2, 0);

	hpBar->setPosition(_winSize.width / 2, 0);
	hpState = Label::create("500/500", fontPath, 30);
	hpState->setColor(Color3B(100, 0, 0));
	hpState->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	hpState->setPosition(_winSize.width / 2, 0);

	ttf1 = Label::create("Default", fontPath, 30);
	ttf1->setPosition(100, 100);
	ttf1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	this->addChild(player);
	this->addChild(ttf1);
	this->addChild(statusBar);
	this->addChild(mpBar);
	this->addChild(hpBar);
	this->addChild(mpState);
	this->addChild(hpState);
	this->addChild(slotBack);

	roundViewer = Label::create("Round", fontPath, 30);
	roundViewer->setColor(Color3B::RED);
	roundViewer->setPosition(_winSize.width / 2, _winSize.height - 20);
	roundViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	this->addChild(roundViewer);

	timeViewer = Label::create(std::to_string(gameTime), fontPath, 30);
	timeViewer->setColor(Color3B::RED);
	timeViewer->setPosition(_winSize.width / 2, _winSize.height - 60);
	timeViewer->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	this->addChild(timeViewer);

	for (int i = 0; i < 6; i++) {
		Sprite* temp = Sprite::create("UI/SkillBox.png");
		temp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		temp->setPosition(_winSize.width / 12 * (i + 3.5), _winSize.height * 1 / 20 * 2);
		Skillboxes.pushBack(temp);
		this->addChild(temp);
	}
}

void HelloWorld::setDebugMode()
{
	if(!debug){
		ttf1->setOpacity(0);
	}
	else {
		ttf1->setOpacity(255);
	}
}

void HelloWorld::setDebugID(int input)
{
	debugID = input;
	if (debugID == 79)
		debug = true;
	else
		debug = false;
	setDebugMode();
}

void HelloWorld::popUpClick()
{
	if (popbutton->getPositionX() > 0) {
		popback->setPosition(-300, _winSize.height / 2);
		pop1->setPosition(-300, _winSize.height / 2);
		pop2->setPosition(-300, _winSize.height / 2);
		pop3->setPosition(-300, _winSize.height / 2);
		popbutton->setPosition(0, _winSize.height / 2);
		popbutton->setRotation(0);
	}
	else {
		popback->setPosition(0, _winSize.height / 2);
		pop1->setPosition(0, _winSize.height / 2);
		pop2->setPosition(0, _winSize.height / 2);
		pop3->setPosition(0, _winSize.height / 2);
		popbutton->setPosition(350, _winSize.height / 2);
		popbutton->setRotation(180);
	}
}

void HelloWorld::makeTower()
{
	tower = Tower::create("Unit/Hostile.png");
	tower->make();
	tower->setPhysicsBitmask(Collisioner::bitmaskPlayerAll, ~(Collisioner::bitmaskBulletOne + Collisioner::bitmaskPlayerAll), Collisioner::bitmaskEnemyAll);
	tower->setDeathCallback(CC_CALLBACK_0(HelloWorld::goGameOver, this));
	tower->setPosition(Vec2(_winSize.width / 2, _winSize.height/2));

	layerMissile->addChild(tower);
}

void HelloWorld::onTimeUpdate(float input)//권태형 제작
{
	Vec2 playerPos = player->getPosition();

	// 플레이어 각도 설정
	player->setRotation(-MathCalculator::calculateAngle(playerPos, mouse) * MathCalculator::radian());
	mpBar->setPercentage(persent(MPCurrent, MPMax));
	std::string mpText = std::to_string(static_cast<int>(ceil(MPCurrent))) + " / " + std::to_string(static_cast<int>(ceil(MPMax)));
	mpState->setString(mpText);

	hpBar->setPercentage(persent(tower->getHPCurrent(), tower->getHPMax()));
	std::string hpText = std::to_string(static_cast<int>(ceil(tower->getHPCurrent()))) + " / " + std::to_string(static_cast<int>(ceil(tower->getHPMax())));
	hpState->setString(hpText);
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
}

void HelloWorld::mpRestore(float input)
{
	MPRegenCount += MPRegenAmount;

	if (MPRegenCount >= _MPSIZERATE)
	{
		MPRegenCount -= _MPSIZERATE;

		if (MPCurrent < MPMax)
			MPCurrent++;
	}
}

void HelloWorld::monsterCreateTimer(float dt)
{
	createCount++;

	if (createCount >= roundCount)
	{
		// 몬스터 생성
		if (monsterPresentAmount < monsterRoundAmount)
		{
			// 몬스터 개체수 표기
			monsterPresentAmount++;
			monsterPresentViewer->setString(std::to_string(monsterPresentAmount));

			// 몬스터 변이 정보 정하기
			int mutateType = 0;
			int mutateLevel = 1;

			if (mutateCreatePer >(rand() % 100))
			{
				while (mutateLevelUpPer > (rand() % 100) && MUTATE_MAXLEVEL)
					mutateLevel++;
				mutateType = (rand() % 5) + 1;
			}

			// 변이 정보로부터 데이터 가져오기


			// 몬스터 생성
			auto monster = Enemy::create("Unit/Hostile_Tank.png");
			monster->make();
			monster->setPhysicsBitmask(Collisioner::bitmaskEnemyAll, ~(Collisioner::bitmaskBulletTwo + Collisioner::bitmaskEnemyAll), Collisioner::bitmaskPlayerAll);
			monster->setPosition(Vec2(_winSize.width * (rand() % 2), (rand() % static_cast<int>(_winSize.height))));
			
			monster->setBaseAbillity(GameData::roundEnemyHP[roundNum], GameData::roundEnemyAttack[roundNum],
				GameData::enemyAttackRange, GameData::enemyMoveSpeed, GameData::enemyAttackSpeed);
			monster->setEnemyAim(tower->getPosition());
			monster->setCreateCallback(CC_CALLBACK_0(HelloWorld::monsterCreate, this));
			monster->setDeathCallback(CC_CALLBACK_0(HelloWorld::monsterDeath, this));
			//monster->setExplodeCallback(CC_CALLBACK_0(HelloWorld::explodeEffect, this, monster->getPosition()));
			//monster->projectImage("Unit/Hostile_Tank.png"); faster 타입에만 적용
			monster->setHpGage("Others/hpGage.png");
			// 변이 적용시키기
			enemyVector.pushBack(monster);
			addChild(monster);
		}

		createCount -= roundCount;

		if (monsterPresentAmount % 4 == 0)
			if (roundCount >= 60)
				roundCount -= 8;
			else
				roundCount -= 3;
	}
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
	auto mousePosition = static_cast<EventMouse*>(event)->getLocation();
	std::string output = "X: " + std::to_string(static_cast<int>(ceil(mousePosition.x))) + " Y: " + std::to_string(static_cast<int>(ceil(mousePosition.y)));
	ttf1->setString(output);
	mousePosition.y = _winSize.height - mousePosition.y;
	player->gotoPoint(mousePosition, MathCalculator::calculateAngle(player->getPosition(), mousePosition) * MathCalculator::radian());

	Rect rect = popbutton->getBoundingBox();
	if (rect.containsPoint(mousePosition) && popbutton->getOpacity() == 255) {
		popUpClick();
	}
	else
		player->gotoPoint(mousePosition, MathCalculator::calculateAngle(player->getPosition(), mousePosition) * MathCalculator::radian());
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
	int tempMP = MPCurrent;
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
		tempMP -= GameData::mpReduce[temp];
		if (tempMP >= 0) {
			fireMissile();
			tempVector.clear();
			for (auto && tempspr : Skillboxes) {
				tempspr->setTexture("UI/SkillBox.png");
			}
			divisonNum = 1;
			MPCurrent = tempMP;
			temp = tempVector.size();
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_R) {
		if (temp > 0) {
			Skillboxes.at(temp - 1)->setTexture("UI/SkillBox.png");
			tempVector.pop_back();
		}
		return;
	}
	if (temp >= SlotLevel) {
		ttf1->setString("You need to enchance your slot level.");
		return;
	}
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
		tempVector.push_back(new Knock());
		Skillboxes.at(temp)->setTexture("Elements/Knock.png");
		break;
	case EventKeyboard::KeyCode::KEY_W:
		tempVector.push_back(new PowerUp());
		Skillboxes.at(temp)->setTexture("Elements/PowerUp.png");
		break;
	case EventKeyboard::KeyCode::KEY_E:
		Skillboxes.at(temp)->setTexture("Elements/Explode.png");
		tempVector.push_back(new Explode());
		break;
	case EventKeyboard::KeyCode::KEY_A:
		tempVector.push_back(new Division());
		Skillboxes.at(temp)->setTexture("Elements/Division.png");
		divisonNum+=tempVector.back()->castEffect(divisonNum);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		Skillboxes.at(temp)->setTexture("Elements/Slow.png");
		tempVector.push_back(new Slow());
		break;
	case EventKeyboard::KeyCode::KEY_D:
		Skillboxes.at(temp)->setTexture("Elements/Mine.png");
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

	setRoundVariable();

	// 업그레이드 불가능 상태로 만들기
	canUpgrade = false;
	roundViewer->setColor(Color3B::RED);
	timeViewer->setColor(Color3B::RED);
}

void HelloWorld::setRoundVariable()
{
	// 몬스터 생성 수
	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
	monsterPresentAmount = 0;
	monsterExistAmount = 0;

	// 이 부분은 수정
	mutateCreatePer = GameData::enemyMutateRate[roundNum];
	mutateLevelUpPer = GameData::enemyLevelUpRate[roundNum];

	roundCount = 2 * secondPerFrame;
	createCount = 0;
}

void HelloWorld::monsterCreate()
{
	monsterExistAmount++;
	monsterExistViewer->setString(std::to_string(monsterExistAmount));
}

void HelloWorld::monsterDeath()
{
	monsterExistAmount--;
	monsterExistViewer->setString(std::to_string(monsterExistAmount));
	// 라운드 변경
  	if (monsterPresentAmount == monsterRoundAmount && monsterExistAmount <= 0)
	{
		// 적용함수 만들 것
		// 남은 시간 1초 남기고 없애기
		int extraTime = gameTime - 1;
		gameTime = gameTime - extraTime;
		
		// 남은 시간만큼 마나 / 타워 체력 회복
		tower->healTower(tower->getHPRegen() * extraTime);
		// 마나 채우기 완전한 알고리즘 아님 수정 필요
		MPRegenCount += MPRegenAmount * secondPerFrame * extraTime;

		// 업그레이드 가능 상태로 만들기
		canUpgrade = true;
		popbutton->setOpacity(255);
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

void HelloWorld::goGameOver()
{
	Scene* pScene = GameOver::scene();

	TransitionScene* pTran = TransitionFade::create(0.5f, pScene);

	Director::sharedDirector()->replaceScene(pTran);
}

bool HelloWorld::anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data)
{
	*((Vec2*)data) = info.contact;

	PhysicsBody* body = info.shape->getBody();

	return false;
}

void HelloWorld::myTick(float dt)
{
	Vec2 point1 = Vec2(240, 160);
	Vec2 point2 = Vec2(390, 160);

	removeChild(_node);
	_node = DrawNode::create();

	Vec2 point3 = point2;

	auto func = CC_CALLBACK_3(HelloWorld::anyRay, this);

	this->getScene()->getPhysicsWorld()->rayCast(func, point1, point2, &point3);
	_node->drawSegment(point1, point2, 1, Color4F::RED);

	if (point2 != point3)
	{
		_node->drawDot(point3, 2, Color4F::BLUE);
	}

	addChild(_node);
}

Missile* HelloWorld::makeMissile()
{
	Missile* missile = Missile::create("Others/Bullet.PNG");
	missile->make();

	missile->setPosition(player->getPosition());

	// 내부 값 설정
	missile->setAttack(20 + tempVector.size() * 20);
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
		Vec2 tempVec = MathCalculator::calculateUnitVec2(player->getPosition(), mouse);
		if (divisonNum > 1) {
			tempVec.x += random() % 100 - 50;
			tempVec.y += random() % 100 - 50;
		}
		missile->getPhysicsBody()->setVelocity(tempVec * missile->getSpeed());
		missile->setPhysicsBitmask(Collisioner::bitmaskBulletOne, ~(Collisioner::bitmaskBulletAll + Collisioner::bitmaskPlayerAll), Collisioner::bitmaskZero);
		missile->setCondition(tempVector);
		missile->castEffect();
		layerMissile->addChild(missile);
	}
}

void HelloWorld::popUpCallback(Ref* pSender)
{
	PopUp *pPopup = static_cast<PopUp *>(pSender); //현재 팝업에 대한 클래스로 캐스팅 

	// 버튼 태그 받기
	int nTag = pPopup->getBtnTag();

	if (nTag == 1)
	{
		//닫기 버튼 이다~~
	}
	else if (nTag == 2)
	{
		//헬프 버튼이다~~
	}
}