#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainHeader.h"
#include "SimpleAudioEngine.h"  
#include "GameOver.h"

const std::string fontPath = "fonts/nasalization-rg.ttf";
class HelloWorld : public cocos2d::Layer
{
// for game algorithm
private:
	int roundNum;	// Round Number

	// variable for gameTimer
	int gameTime;	// Round / Set Up Time
	bool isRound;	// check Round state
	bool canUpgrade;	// check Monster remain

	// variable for random mutate
	int mutateCreatePer;		// 변이 생성률
	int mutateLevelUpPer;		// 변이 진화 확률

	// 적군 생성관련 변수
	int monsterRoundAmount;		// 라운드에 생성되는 총 적군 수
	int monsterPresentAmount;	// 지금까지 라운드에 생성된 총 적군 수
	int monsterExistAmount;		// 현재 존재하는 적군 수

	int roundCount;				// 라운드 별 적군 생성 주기
	int createCount;			// 적군 생성 카운트
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

	// 터치 이벤트
	void onTouchesEnded(const std::vector<Touch*> &touches, Event* event);

	//게임 씬의 구현
	void createGameScene();
	void setMonsterAmountViewer();
	void initGameVariable();
	void makeTower();

	//매 시간마다 스케줄링 되는 함수들
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// 타이머 관련 함수
	void mpRestore(float input);		// MP회복함수
	void monsterCreateTimer(float dt);	// 몬스터 생성 주기 함수

	//마우스 이벤트들
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event) {};
	void onMouseScroll(cocos2d::Event* event) {};

	//키보드 이벤트들
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// 라운드 변경시 호출하는 함수
	void roundChange();
	void setRoundVariable();

	// 콜백 함수
	void monsterDeath();
	void explodeEffect(Vec2 point);
	void goGameOver();

	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);
	void myTick(float dt);

	// 객체 생성 함수
	Enemy* makeMonster();
	Missile *makeMissile();
	void fireMissile();

	void setDebugMode();
	void setDebugID(int input);
private:
	Player* player;

	Tower* tower;

	Size _winSize;
	Sprite* Background;
	Layer* layerMissile;
	Sprite* statusBar;

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
	Vec2 diffUnitVec2;
	Vec2 diffUnitVec3;
	float cursorAngle;
	std::vector<Condition*> tempVector;
	Vector<Enemy*> enemyVector;

	DrawNode *_node;

	//분열 관련 변수
	int divisonNum;

	//Skill UI
	Vector<Sprite*> Skillboxes;
	Vector<Label*> SkillLevels;

	//스킬 슬롯 레벨
	unsigned int SlotLevel;

	//기본 능력치
	unsigned int MP;
	int MPMax;

	//Activate Debug
	bool debug;
	int debugID;
};
//마우스 좌표와 특정 시점과의 각도를 계산
// 삭제 : Vec2 계산으로 더 간단하게 가능해서...
float calculateDegree(Vec2 current, Vec2 point);

#endif // __HELLOWORLD_SCENE_H__
