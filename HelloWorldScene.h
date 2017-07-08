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
	int mutateCreatePer;		// ���� ������
	int mutateLevelUpPer;		// ���� ��ȭ Ȯ��

	// ���� �������� ����
	int monsterRoundAmount;		// ���忡 �����Ǵ� �� ���� ��
	int monsterPresentAmount;	// ���ݱ��� ���忡 ������ �� ���� ��
	int monsterExistAmount;		// ���� �����ϴ� ���� ��

	int roundCount;				// ���� �� ���� ���� �ֱ�
	int createCount;			// ���� ���� ī��Ʈ
public:
	// start function
    static cocos2d::Scene* createScene(int input);
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
	void setMonsterAmountViewer();
	void initGameVariable();
	void makeTower();

	//�� �ð����� �����ٸ� �Ǵ� �Լ���
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// Ÿ�̸� ���� �Լ�
	void mpRestore(float input);		// MPȸ���Լ�
	void monsterCreateTimer(float dt);	// ���� ���� �ֱ� �Լ�

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
	void setRoundVariable();

	// �ݹ� �Լ�
	void monsterDeath();
	void explodeEffect(Vec2 point);
	void goGameOver();

	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);
	void myTick(float dt);

	// ��ü ���� �Լ�
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

	
	// 12�� ���� �ð� ǥ��
	Label* roundViewer;
	Label* timeViewer;

	// 1�� ���� ���� �� ǥ��
	Label* monsterPresentViewer;
	Label* monsterExistViewer;

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
	Vector<Label*> SkillLevels;

	//��ų ���� ����
	unsigned int SlotLevel;

	//�⺻ �ɷ�ġ
	unsigned int MP;
	int MPMax;

	//Activate Debug
	bool debug;
	int debugID;
};
//���콺 ��ǥ�� Ư�� �������� ������ ���
// ���� : Vec2 ������� �� �����ϰ� �����ؼ�...
float calculateDegree(Vec2 current, Vec2 point);

#endif // __HELLOWORLD_SCENE_H__
