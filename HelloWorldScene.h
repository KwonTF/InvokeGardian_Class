#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define __DEBUG_GAME_VARIABLE__

#include "cocos2d.h"
#include "MainHeader.h"

class HelloWorld : public cocos2d::Layer
{
// for game algorithm
private:
	int roundNum;	// Round Number

	// variable for gameTimer
	int gameTime;	// Round / Set Up Time
	bool isRound;	// check Round state

	// variable for random mutate
	int mutateArray[5];		// Array for saving mutate information
	int mutateBasePer;		// Base Persent of mutate
	int mutateRoundPer;		// Round Persent of mutate
	int mutateRoundBonus;	// 

	// variable for monster create
	int monsterBaseAmount;		// 기본적으로 생성하는 몬스터 수
	int monsterRoundAmount;		// 라운드에 생성되는 총 몬스터 수
	int monsterPresentAmount;	// 현재 나온 몬스터 수
public:
	// start function
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	// make PhysicsWorld
	cocos2d::PhysicsWorld* m_world;

	void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }

	// 충돌시 처리
	bool onContactBegin(cocos2d::PhysicsContact& Contact);

	//게임 씬의 구현
	void createGameScene();
	void initGameVariable();
	void makeTower();
	//매 시간마다 스케줄링 되는 함수들
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// 타이머 관련 함수
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

	// 객체 생성 함수
	Enemy* makeMonster();
	Missile *makeMissile();
	void fireMissile();
private:
	Layer* layerMissile;
	Player* player;
	Sprite* statusBar;
	LabelTTF* ttf1;

	Tower* tower;
	
	// 12시 방향 시간 표기
	LabelTTF* roundViewer;
	LabelTTF* timeViewer;

	Vec2 mouse;
	Vec2 diffUnitVec2;
	float cursorAngle;
	std::vector<Condition*> tempVector;
#ifdef __DEBUG_GAME_VARIABLE__
private:
	LabelTTF* monsterAmountViewer;
	LabelTTF* currentMonsterViewer;
public:
	void setMonsterAmountViewer();
#endif // __DEBUG_GAME_VARIABLE__
};
//스프라이트의 앵커포인트를 가운데로 맞춰준다.
void setSpriteAnchor_Center(Sprite *input);
//마우스 좌표와 특정 시점과의 각도를 계산
// 삭제 : Vec2 계산으로 더 간단하게 가능해서...
float calculateDegree(Vec2 current, Vec2 point);

#endif // __HELLOWORLD_SCENE_H__
