#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define __DEBUG_GAME_VARIABLE__

#include "cocos2d.h"
#include "MainHeader.h"
#include "SimpleAudioEngine.h"  

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

	// ��ġ �̺�Ʈ
	void onTouchesEnded(const std::vector<Touch*> &touches, Event* event);

	//���� ���� ����
	void createGameScene();
	void initGameVariable();
	void makeTower();
	//�� �ð����� �����ٸ� �Ǵ� �Լ���
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// Ÿ�̸� ���� �Լ�
	void mpRestore(float input); // MPȸ���Լ�
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

	void monsterDeath();
	void explodeEffect(Vec2 point);
	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);
	void myTick(float dt);
	// ��ü ���� �Լ�
	Enemy* makeMonster();
	Missile *makeMissile();
	void fireMissile();
private:
	Size _winSize;
	Sprite* Background;
	Layer* layerMissile;
	Player* player;
	Sprite* statusBar;

	Sprite* mpSprite;
	CCProgressTimer* mpBar;
	LabelTTF* mpState;

	Sprite* hpSprite;
	CCProgressTimer* hpBar;
	LabelTTF* hpState;

	LabelTTF* ttf1;

	Tower* tower;
	
	// 12�� ���� �ð� ǥ��
	LabelTTF* roundViewer;
	LabelTTF* timeViewer;

	Vec2 mouse;
	Vec2 diffUnitVec2;
	Vec2 diffUnitVec3;
	float cursorAngle;
	std::vector<Condition*> tempVector;
	Vector<Enemy*> enemyVector;

	DrawNode *_node;

	//�п� ���� ����
	int divisonNum;

	//Skill UI
	Vector<Sprite*> Skillboxes;
	Vector<LabelTTF*> SkillLevels;

	//��ų ���� ����
	unsigned int SlotLevel;

	//�⺻ �ɷ�ġ
	unsigned int MP;
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
