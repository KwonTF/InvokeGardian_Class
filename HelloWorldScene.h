#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainHeader.h"
#include "SimpleAudioEngine.h"  
#include "GameOver.h"

inline float persent(int Current, int Max) { return (Current * 100) / Max; }

const std::string fontPath = "fonts/nasalization-rg.ttf";
class HelloWorld : public cocos2d::Layer
{
// for game algorithm
private:
	int roundNum;	// Round Number

	// variable for gameTimer
	int gameTime;	// Round / Set Up Time
	bool isRound;	// check Round state

	// variable for random mutate
	int mutateCreatePer;		// 변이 생성률
	int mutateLevelUpPer;		// 변이 진화 확률

	// 적군 생성관련 변수
	int monsterRoundAmount;		// 라운드에 생성되는 총 적군 수
	int monsterPresentAmount;	// 지금까지 라운드에 생성된 총 적군 수
	int monsterExistAmount;		// 현재 존재하는 적군 수

	int roundCount;				// 라운드 별 적군 생성 주기
	int createCount;			// 적군 생성 카운트

	// 기본 능력치
	int MPCurrent;				// 현재 마나
	int MPMax;					// 마나 최대치
	int MPRegenCount;			// 마나 리젠 카운트
	int MPRegenAmount;			// 마나 리젠량
	int SlotLevel;				// 최대 조합 수

	// 업그레이드 관련
	int money;					// 업그레이드 돈
	bool canUpgrade;			// 업그레이드 가능 여부 조사
	bool isUpgradeOpen;			// 업그레이드창 개폐 여부
	int upgradeLayerNum;

	//Activate Debug
	bool debug;
	int debugID;
	bool isDebugVisible;

public:
	// start function
    static cocos2d::Scene* createScene(int input);
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	// make PhysicsWorld
	cocos2d::PhysicsWorld* m_world;

	void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }

	// 충돌시 처리
	bool onContactBegin(cocos2d::PhysicsContact& Contact);

	//게임 씬의 구현
	void createGameScene();
	void setMonsterAmountViewer();
	void makeUpgradeWindow();
	void initGameVariable();
	void makeTower();

	//매 시간마다 스케줄링 되는 함수들
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// 타이머 관련 함수
	void mpRestore(float input);		// MP회복함수
	void monsterCreateTimer(float dt);	// 몬스터 생성 주기 함수
										
	// 터치 이벤트
	void onTouchesEnded(const std::vector<Touch*> &touches, Event* event);

	//마우스 이벤트들
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event) {};
	void onMouseScroll(cocos2d::Event* event) {};

	// 키보드 이벤트들
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// 버튼 터치 이벤트들
	void skipButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void endButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeOpenerTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeChangeTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeEnhanceTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void debugVisibleTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);

	// 라운드 변경시 호출하는 함수
	void roundEnd();
	void roundChange();
	void timeSkip();
	void setRoundVariable();

	// 콜백 함수
	void monsterCreate();
	void monsterDeath();
	void explodeEffect(Vec2 point);
	void goGameOver();

	// Raycast 관련 함수
	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);
	void myTick(float dt);

	// 객체 생성 함수
	Missile *makeMissile();
	void fireMissile();

	// UI 관련 함수
	void UISetting();
	void popUpCallback(Ref* pSender);
	void popUpClick();

	// 디버그 관련 함수
	void debugFuncVisible();
	void setDebugMode();
	void setDebugID(int input);
private:
	Player* player;
	Tower* tower;

	Size _winSize;
	Sprite* Background;
	Layer* layerMissile;
	Sprite* statusBar;

	Node* upgradeWindow;
	ui::Button* upgradeOpener;
	Layer* upgradeElement;
	Layer* upgradeTower;
	Layer* upgradeGuardian;
	Sprite* popbutton;
	Sprite* popback;
	Sprite* pop1;
	Sprite* pop2;
	Sprite* pop3;

	ui::Button* upEKnock;
	ui::Button* upEPower;
	ui::Button* upEExplo;
	ui::Button* upEDiv;
	ui::Button* upESlow;
	ui::Button* upEMine;

	ui::Button* upGMP;
	ui::Button* upGHP;
	ui::Button* upGSlot;

	ui::Button* upgradeElementSelector;
	ui::Button* upgradeTowerSelector;
	ui::Button* upgradeGuardianSelector;

	ui::Button* setupSkip;
	ui::Button* roundEnder;
	ui::Button* debugVisibler;

	Sprite* mpSprite;
	CCProgressTimer* mpBar;
	Label* mpState;

	Sprite* hpSprite;
	CCProgressTimer* hpBar;
	Label* hpState;

	Label* ttf1;

	// 12시 방향 시간 표기
	Label* roundViewer;
	Label* timeViewer;

	// 1시 방향 적군 수 표기
	Label* monsterPresentViewer;
	Label* monsterExistViewer;

	Vec2 mouse;
	std::vector<Condition*> conditionInfoArray;
	std::vector<Condition*> tempVector;
	Vector<Enemy*> enemyVector;

	DrawNode *_node;

	//분열 관련 변수
	int divisonNum;

	//Skill UI
	Vector<Sprite*> Skillboxes;
	Vector<Label*> SkillLevels;


};
#endif // __HELLOWORLD_SCENE_H__
