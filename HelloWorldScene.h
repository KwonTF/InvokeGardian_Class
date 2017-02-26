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
	int monsterBaseAmount;		// �⺻������ �����ϴ� ���� ��
	int monsterRoundAmount;		// ���忡 �����Ǵ� �� ���� ��
	int monsterPresentAmount;	// ���� ���� ���� ��
public:
	// start function
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	// make PhysicsWorld
	cocos2d::PhysicsWorld* m_world;

	void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }

	// �浹�� ó��
	bool onContactBegin(cocos2d::PhysicsContact& Contact);

	//���� ���� ����
	void createGameScene();
	void initGameVariable();
	void makeTower();
	//�� �ð����� �����ٸ� �Ǵ� �Լ���
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// Ÿ�̸� ���� �Լ�
	//���콺 �̺�Ʈ��
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event) {};
	void onMouseScroll(cocos2d::Event* event) {};
	//Ű���� �̺�Ʈ��
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ���� ����� ȣ���ϴ� �Լ�
	void roundChange();

	// ��ü ���� �Լ�
	Enemy* makeMonster();
	Missile *makeMissile();
	void fireMissile();
private:
	Layer* layerMissile;
	Player* player;
	Sprite* statusBar;
	LabelTTF* ttf1;

	Tower* tower;
	
	// 12�� ���� �ð� ǥ��
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
//��������Ʈ�� ��Ŀ����Ʈ�� ����� �����ش�.
void setSpriteAnchor_Center(Sprite *input);
//���콺 ��ǥ�� Ư�� �������� ������ ���
// ���� : Vec2 ������� �� �����ϰ� �����ؼ�...
float calculateDegree(Vec2 current, Vec2 point);

#endif // __HELLOWORLD_SCENE_H__
