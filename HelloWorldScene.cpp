﻿#include "HelloWorldScene.h"
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
	Background = Sprite::create("Background/playScene.png");
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
	makeUpgradeWindow();
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

	conditionInfoArray.push_back(new Knock());
	conditionInfoArray.push_back(new PowerUp());
	conditionInfoArray.push_back(new Explode());
	conditionInfoArray.push_back(new Division());
	conditionInfoArray.push_back(new Slow());
	conditionInfoArray.push_back(new Mine());
	SlotLevel = 2;

	roundNum = 1;

	gameTime = ROUNDTIME;
	isRound = true;
	canUpgrade = false;
	upgradeLayerNum = 3;

	monsterExistAmount = 0;
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

void HelloWorld::makeUpgradeWindow()
{
	upgradeWindow = Node::create();
	upgradeWindow->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	upgradeWindow->setPosition(0, _winSize.height / 2);

	// 
	upgradeOpener = ui::Button::create();
	upgradeOpener->setTouchEnabled(true);
	upgradeOpener->loadTextures("UI/PopButton.png", "UI/PopButton.png", "UI/PopButton.png");
	upgradeOpener->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeOpenerTouch, this));
	upgradeOpener->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	upgradeWindow->addChild(upgradeOpener);

	// for UI check
	popback = Sprite::create("UI/PopBack.png");
	popback->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	upgradeWindow->addChild(popback);

	upgradeElement = Layer::create();
	upgradeWindow->addChild(upgradeElement);
	upgradeTower = Layer::create();
	upgradeWindow->addChild(upgradeTower);
	upgradeGuardian = Layer::create();
	upgradeWindow->addChild(upgradeGuardian);

	pop1 = Sprite::create("UI/Popup_1.png");
	pop1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	upgradeElement->addChild(pop1);
	pop2 = Sprite::create("UI/Popup_2.png");
	pop2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	upgradeTower->addChild(pop2);
	pop3 = Sprite::create("UI/Popup_3.png");
	pop3->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	upgradeGuardian->addChild(pop3);

	// upgrade Button
	upEKnock = ui::Button::create();
	upEKnock->setTouchEnabled(true);
	upEKnock->loadTextures("Elements/Knock.png", "Elements/KnockClick.png", "Elements/KnockClick.png");
	upEKnock->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upEKnock->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT); 
	upEKnock->setPosition(Vec2(-290, _winSize.height / 2 - 90));
	upEKnock->setTag(1);
	upgradeElement->addChild(upEKnock);

	upEPower = ui::Button::create();
	upEPower->setTouchEnabled(true);
	upEPower->loadTextures("Elements/PowerUp.png", "Elements/PowerUpClick.png", "Elements/PowerUpClick.png");
	upEPower->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upEPower->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upEPower->setPosition(Vec2(-290, _winSize.height / 2 - 180));
	upEPower->setTag(2);
	upgradeElement->addChild(upEPower);

	upEExplo = ui::Button::create();
	upEExplo->setTouchEnabled(true);
	upEExplo->loadTextures("Elements/Knock.png", "Elements/KnockClick.png", "Elements/KnockClick.png");
	upEExplo->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upEExplo->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upEExplo->setPosition(Vec2(-290, _winSize.height / 2 - 270));
	upEExplo->setTag(3);
	upgradeElement->addChild(upEExplo);

	upEDiv = ui::Button::create();
	upEDiv->setTouchEnabled(true);
	upEDiv->loadTextures("Elements/Division.png", "Elements/DivisionClick.png", "Elements/DivisionClick.png");
	upEDiv->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upEDiv->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upEDiv->setPosition(Vec2(-290, _winSize.height / 2 - 360));
	upEDiv->setTag(4);
	upgradeElement->addChild(upEDiv);

	upESlow = ui::Button::create();
	upESlow->setTouchEnabled(true);
	upESlow->loadTextures("Elements/Slow.png", "Elements/SlowClick.png", "Elements/SlowClick.png");
	upESlow->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upESlow->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upESlow->setPosition(Vec2(-290, _winSize.height / 2 - 450));
	upESlow->setTag(5);
	upgradeElement->addChild(upESlow);

	upEMine = ui::Button::create();
	upEMine->setTouchEnabled(true);
	upEMine->loadTextures("Elements/Mine.png", "Elements/MineClick.png", "Elements/MineClick.png");
	upEMine->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upEMine->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upEMine->setPosition(Vec2(-290, _winSize.height / 2 - 540));
	upEMine->setTag(6);
	upgradeElement->addChild(upEMine);

	upGMP = ui::Button::create();
	upGMP->setTouchEnabled(true);
	upGMP->loadTextures("UI/upMP.png", "UI/upMPClick.png", "UI/upMPClick.png");
	upGMP->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upGMP->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upGMP->setPosition(Vec2(-290, _winSize.height / 2 - 90));
	upGMP->setTag(1);
	upgradeGuardian->addChild(upGMP);

	upGHP = ui::Button::create();
	upGHP->setTouchEnabled(true);
	upGHP->loadTextures("UI/upHP.png", "UI/upHPClick.png", "UI/upHPClick.png");
	upGHP->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upGHP->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upGHP->setPosition(Vec2(-290, _winSize.height / 2 - 210));
	upGHP->setTag(2);
	upgradeGuardian->addChild(upGHP);

	upGSlot = ui::Button::create();
	upGSlot->setTouchEnabled(true);
	upGSlot->loadTextures("UI/upElement.png", "UI/upElementClick.png", "UI/upElementClick.png");
	upGSlot->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeEnhanceTouch, this));
	upGSlot->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upGSlot->setPosition(Vec2(-290, _winSize.height / 2 - 330));
	upGSlot->setTag(3);
	upgradeGuardian->addChild(upGSlot);

	

	// Layer Selecor
	upgradeElementSelector = ui::Button::create();
	upgradeElementSelector->setTouchEnabled(true);
	upgradeElementSelector->loadTextures("UI/Tab_1N.png", "UI/Tab_1S.png", "UI/Tab_1D.png");
	upgradeElementSelector->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeChangeTouch, this));
	upgradeElementSelector->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	upgradeElementSelector->setPositionY(_winSize.height / 2);
	upgradeElementSelector->setTag(1);
	upgradeWindow->addChild(upgradeElementSelector);

	upgradeTowerSelector = ui::Button::create();
	upgradeTowerSelector->setTouchEnabled(true);
	upgradeTowerSelector->loadTextures("UI/Tab_2N.png", "UI/Tab_2S.png", "UI/Tab_2D.png");
	upgradeTowerSelector->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeChangeTouch, this));
	upgradeTowerSelector->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	upgradeTowerSelector->setPositionY(_winSize.height / 2 - popLayerBtnSizeY);
	upgradeTowerSelector->setTag(2);
	upgradeWindow->addChild(upgradeTowerSelector);

	upgradeGuardianSelector = ui::Button::create();
	upgradeGuardianSelector->setTouchEnabled(true);
	upgradeGuardianSelector->loadTextures("UI/Tab_3N.png", "UI/Tab_3S.png", "UI/Tab_3D.png");
	upgradeGuardianSelector->addTouchEventListener(CC_CALLBACK_2(HelloWorld::upgradeChangeTouch, this));
	upgradeGuardianSelector->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	upgradeGuardianSelector->setPositionY(_winSize.height / 2 - popLayerBtnSizeY * 2);
	upgradeGuardianSelector->setTag(3);
	upgradeWindow->addChild(upgradeGuardianSelector);

	addChild(upgradeWindow);
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

	setupSkip = ui::Button::create();
	setupSkip->setTouchEnabled(true);
	setupSkip->loadTextures("UI/SkipButtonN.png", "UI/SkipButtonS.png", "UI/SkipButtonD.png");
	setupSkip->addTouchEventListener(CC_CALLBACK_2(HelloWorld::skipButtonTouch, this));
	setupSkip->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	setupSkip->setPosition(Vec2(_winSize.width, _winSize.height * 4 / 5));
	addChild(setupSkip);

	roundEnder = ui::Button::create();
	roundEnder->setTouchEnabled(true);
	roundEnder->loadTextures("UI/RoundUpN.png", "UI/RoundUpS.png", "UI/RoundUpD.png");
	roundEnder->addTouchEventListener(CC_CALLBACK_2(HelloWorld::endButtonTouch, this));
	roundEnder->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	roundEnder->setPosition(Vec2(_winSize.width, _winSize.height * 3 / 5));
	addChild(roundEnder);
	
}

void HelloWorld::setDebugMode()
{
	isDebugVisible = false;
	debugFuncVisible();

	if(!debug){
		ttf1->setOpacity(0);
	}
	else {
		ttf1->setOpacity(255);

		debugVisibler = ui::Button::create();
		debugVisibler->setTouchEnabled(true);
		debugVisibler->loadTextures("UI/skipS.png", "UI/skipS.png", "UI/skipS.png");
		debugVisibler->addTouchEventListener(CC_CALLBACK_2(HelloWorld::debugVisibleTouch, this));
		debugVisibler->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		debugVisibler->setPosition(Vec2(_winSize.width, _winSize.height * 1 / 5));
		addChild(debugVisibler);
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

void HelloWorld::debugFuncVisible()
{
	monsterPresentViewer->setVisible(isDebugVisible);
	monsterExistViewer->setVisible(isDebugVisible);
	roundEnder->setVisible(isDebugVisible);
	roundEnder->setEnabled(isDebugVisible);
}

void HelloWorld::popUpClick()
{
	if (isUpgradeOpen) 
	{
		isUpgradeOpen = false;
		upgradeWindow->setPosition(300, _winSize.height / 2);
	}
	else 
	{
		isUpgradeOpen = true;
		upgradeWindow->setPosition(0, _winSize.height / 2);
	}
}

void HelloWorld::makeTower()
{
	tower = Tower::create("Unit/tower_base.png");
	tower->make();
	tower->setPhysicsBitmask(Collisioner::bitmaskPlayerAll, ~(Collisioner::bitmaskBulletOne + Collisioner::bitmaskPlayerAll), Collisioner::bitmaskEnemyAll);
	tower->setDeathCallback(CC_CALLBACK_0(HelloWorld::goGameOver, this));
	tower->setDeathAnimFile(GameData::enemyDeathAnimation, 12);
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
		roundChange();

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
			Mutate *m = new Mutate();
			m->setMutateInfo(mutateType, mutateLevel, GameData::enemyMutateStatus[mutateLevel][mutateType][0],
				GameData::enemyMutateStatus[mutateLevel][mutateType][1], GameData::enemyMutateStatus[mutateLevel][mutateType][2],
				GameData::enemyMutateStatus[mutateLevel][mutateType][3], GameData::enemyMutateStatus[mutateLevel][mutateType][4]);
			m->setImageInfo(GameData::enemyMutateImage[mutateLevel][mutateType]);

			// 몬스터 생성
			auto monster = Enemy::create(m->imageName);
			monster->make();
			monster->setPhysicsBitmask(Collisioner::bitmaskEnemyAll, ~(Collisioner::bitmaskBulletTwo + Collisioner::bitmaskEnemyAll), Collisioner::bitmaskPlayerAll);
			monster->setPosition(Vec2(_winSize.width * (rand() % 2), (rand() % static_cast<int>(_winSize.height))));
			// 파일 설정
			monster->setDeathAnimFile(GameData::enemyDeathAnimation, 12);
			monster->setMissileDeathAnimFile(GameData::eMissileBoomAnimation, 6);
			// 기본 능력치 설정
			monster->setBaseAbillity(GameData::roundEnemyHP[roundNum], GameData::roundEnemyAttack[roundNum],
				GameData::enemyAttackRange, GameData::enemyMoveSpeed, GameData::enemyAttackSpeed);
			monster->setEnemyAim(tower->getPosition());
			// 콜백 적용
			monster->setCreateCallback(CC_CALLBACK_0(HelloWorld::monsterCreate, this));
			monster->setDeathCallback(CC_CALLBACK_0(HelloWorld::monsterDeath, this));
			monster->setHpGage("Others/hpGage.png");
			// 변이 적용시키기(nF)
			monster->setParentLayer(layerMissile);
			monster->typeEnhance(*m);

			//enemyVector.pushBack(monster);
			layerMissile->addChild(monster);
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
		tempVector.push_back(new Knock(*(static_cast<Knock *>(conditionInfoArray.at(0)))));
		Skillboxes.at(temp)->setTexture("Elements/Knock.png");
		break;
	case EventKeyboard::KeyCode::KEY_W:
		tempVector.push_back(new PowerUp(*(static_cast<PowerUp *>(conditionInfoArray.at(1)))));
		Skillboxes.at(temp)->setTexture("Elements/PowerUp.png");
		break;
	case EventKeyboard::KeyCode::KEY_E:
		tempVector.push_back(new Explode(*(static_cast<Explode *>(conditionInfoArray.at(2)))));
		Skillboxes.at(temp)->setTexture("Elements/Explode.png");
		break;
	case EventKeyboard::KeyCode::KEY_A:
		tempVector.push_back(new Division(*(static_cast<Division *>(conditionInfoArray.at(3)))));
		Skillboxes.at(temp)->setTexture("Elements/Division.png");
		divisonNum += tempVector.back()->castEffect(divisonNum);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		tempVector.push_back(new Slow(*(static_cast<Slow *>(conditionInfoArray.at(4)))));
		Skillboxes.at(temp)->setTexture("Elements/Slow.png");
		break;
	case EventKeyboard::KeyCode::KEY_D:
		tempVector.push_back(new Mine(*(static_cast<Mine *>(conditionInfoArray.at(5)))));
		Skillboxes.at(temp)->setTexture("Elements/Mine.png");
		break;
	default:
		break;
	}
}

void HelloWorld::skipButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
		timeSkip();
}

void HelloWorld::endButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		if (isRound)
		{
			roundChange();
			roundChange();
		}
	}
}

void HelloWorld::upgradeOpenerTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
		popUpClick();
}

void HelloWorld::upgradeChangeTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		int btnTag = (static_cast<ui::Button*>(pSender))->getTag();

		if (btnTag == 1)
		{
			cocos2d::log("btn 1");
			upgradeElement->setZOrder(3);
			upgradeTower->setZOrder(0);
			upgradeGuardian->setZOrder(0);
			upgradeLayerNum = 1;
		}
		if (btnTag == 2)
		{
			cocos2d::log("btn 2");
			upgradeElement->setZOrder(0);
			upgradeTower->setZOrder(3);
			upgradeGuardian->setZOrder(0);
			upgradeLayerNum = 2;
		}
		if (btnTag == 3)
		{
			cocos2d::log("btn 3");
			upgradeElement->setZOrder(0);
			upgradeTower->setZOrder(0);
			upgradeGuardian->setZOrder(3);
			upgradeLayerNum = 3;
		}
	}
}

void HelloWorld::upgradeEnhanceTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		int btnTag = (static_cast<ui::Button*>(pSender))->getTag();

		auto tempLevel = Sprite::create("UI/SkillPts.png");
		tempLevel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

		if (upgradeLayerNum == 1)
		{
			// 주의 : 업글 상태 6 넘어가면 기묘해짐
			switch (btnTag) {
			case 1:
				cocos2d::log("Knock");
				conditionInfoArray.at(0)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(0)->conditionLevel, _winSize.height / 2 - 91));
				break;
			case 2:
				cocos2d::log("Knock");
				conditionInfoArray.at(1)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(1)->conditionLevel, _winSize.height / 2 - 181));
				break;
			case 3:
				cocos2d::log("Knock");
				conditionInfoArray.at(2)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(2)->conditionLevel, _winSize.height / 2 - 271));
				break;
			case 4:
				cocos2d::log("Knock");
				conditionInfoArray.at(3)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(3)->conditionLevel, _winSize.height / 2 - 361));
				break;
			case 5:
				cocos2d::log("Knock");
				conditionInfoArray.at(4)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(4)->conditionLevel, _winSize.height / 2 - 451));
				break;
			case 6:
				cocos2d::log("Knock");
				conditionInfoArray.at(5)->enchance();
				tempLevel->setPosition(Vec2(-260 + 30 * conditionInfoArray.at(5)->conditionLevel, _winSize.height / 2 - 541));
				break;
			}
			upgradeElement->addChild(tempLevel);
		}
		if (upgradeLayerNum == 2)
		{
		}
		if (upgradeLayerNum == 3)
		{
			// 주의 : 업글 상태 4 넘어가면 기묘해짐
			switch (btnTag) {
			case 1:
				tempLevel->setPosition(Vec2(-250 + 30 * (MPMax / 50 - 1), _winSize.height / 2 - 91));
				MPMax += 50;
				MPRegenAmount += 2;
				break;
			case 2:
				tempLevel->setPosition(Vec2(-250 + 30 * (tower->getHPMax() / 500), _winSize.height / 2 - 211));
				tower->setHP(tower->getHPMax() + 500);
				break;
			case 3:
				tempLevel->setPosition(Vec2(-250 + 30 * (SlotLevel - 1), _winSize.height / 2 - 331));
				SlotLevel++;
				break;
			}
			upgradeGuardian->addChild(tempLevel);
		}
	}
}

void HelloWorld::debugVisibleTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		if (isDebugVisible)
			isDebugVisible = false;
		else
			isDebugVisible = true;

		debugFuncVisible();
	}
}

/*
적군을 다 잡으면 효과를 적용하는 함수
*/
void HelloWorld::roundEnd()
{
	// Round -> Set Up일때만 실행
	if (isRound == true)
		timeSkip();

	// 라운드 결과 돈 획득

	// 업그레이드 가능 상태로 만들기
	canUpgrade = true;
	roundViewer->setColor(Color3B::GREEN);
	timeViewer->setColor(Color3B::GREEN);
}

/*
Round가 바뀔 때 변수들을 다시 초기화하는 함수
create by ZeroFe
*/
void HelloWorld::roundChange()
{
	// Round -> Set Up
	if (isRound == true)
	{
		isRound = false;
		gameTime = SETUPTIME;

		roundViewer->setString("SETUP");
	}
	// Set Up -> Round
	else
	{
		isRound = true;
		gameTime = ROUNDTIME;
		roundNum++;
		setRoundVariable();

		roundViewer->setString("ROUND ");

		// 업그레이드 불가능 상태로 만들기
		canUpgrade = false;
		roundViewer->setColor(Color3B::RED);
		timeViewer->setColor(Color3B::RED);

		cocos2d::log("round %d", roundNum);
	}
}

// 남은 시간을 생략하고 회복하는 함수
void HelloWorld::timeSkip()
{
	// 남은 시간 1초 남기고 없애기
	int extraTime = gameTime - 1;
	gameTime = gameTime - extraTime;

	// 남은 시간만큼 마나 / 타워 체력 회복
	tower->healTower(tower->getHPRegen() * extraTime);
	MPRegenCount += MPRegenAmount * secondPerFrame * extraTime;
}

void HelloWorld::setRoundVariable()
{
	// 몬스터 생성 수
	monsterRoundAmount = monsterBaseAmount + 4 * roundNum;
	monsterPresentAmount = 0;
	//monsterExistAmount = 0;

	// 변이 관련 변수
	mutateCreatePer = GameData::enemyMutateRate[roundNum];
	mutateLevelUpPer = GameData::enemyLevelUpRate[roundNum];

	// 생성 주기 변수
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
		roundEnd();
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
	missile->setAttack(20);
	return missile;
}

void HelloWorld::fireMissile()
{
	// Missile로 만든거
	for (int i = 0; i < divisonNum; i++) 
	{
		auto missile = HelloWorld::makeMissile();
		Vec2 tempVec = MathCalculator::calculateUnitVec2(player->getPosition(), mouse);
		if (divisonNum > 1) 
		{
			tempVec = tempVec.rotate(MathCalculator::calculateRotateVec2(-(divisonNum-1) * 7.5 / MathCalculator::radian()));
			tempVec = tempVec.rotate(MathCalculator::calculateRotateVec2(i * 15 / MathCalculator::radian()));
		}
		missile->getPhysicsBody()->setVelocity(tempVec * missile->getSpeed());
		missile->setPhysicsBitmask(Collisioner::bitmaskBulletOne, ~(Collisioner::bitmaskBulletAll + Collisioner::bitmaskPlayerAll), Collisioner::bitmaskZero);
		missile->setDeathAnimFile(GameData::pMissileBoomAnimation, 4);
		missile->setDeathAnimFile2(GameData::missileBoomAnimation, 8, 8, 100, 100, 1/30);
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