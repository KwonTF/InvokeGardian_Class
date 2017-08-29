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
	int mutateCreatePer;		// ���� ������
	int mutateLevelUpPer;		// ���� ��ȭ Ȯ��

	// ���� �������� ����
	int monsterRoundAmount;		// ���忡 �����Ǵ� �� ���� ��
	int monsterPresentAmount;	// ���ݱ��� ���忡 ������ �� ���� ��
	int monsterExistAmount;		// ���� �����ϴ� ���� ��

	int roundCount;				// ���� �� ���� ���� �ֱ�
	int createCount;			// ���� ���� ī��Ʈ

	// �⺻ �ɷ�ġ
	int MPCurrent;				// ���� ����
	int MPMax;					// ���� �ִ�ġ
	int MPRegenCount;			// ���� ���� ī��Ʈ
	int MPRegenAmount;			// ���� ������
	int SlotLevel;				// �ִ� ���� ��

	// ���׷��̵� ����
	int money;					// ���׷��̵� ��
	bool canUpgrade;			// ���׷��̵� ���� ���� ����
	bool isUpgradeOpen;			// ���׷��̵�â ���� ����
	int upgradeLayerNum;

	//Activate Debug
	bool debug;
	int debugID;

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

	//���� ���� ����
	void createGameScene();
	void setMonsterAmountViewer();
	void makeUpgradeWindow();
	void initGameVariable();
	void makeTower();

	//�� �ð����� �����ٸ� �Ǵ� �Լ���
	void onTimeUpdate(float input);		// 
	void gameTimer(float dt);			// Ÿ�̸� ���� �Լ�
	void mpRestore(float input);		// MPȸ���Լ�
	void monsterCreateTimer(float dt);	// ���� ���� �ֱ� �Լ�
										
	// ��ġ �̺�Ʈ
	void onTouchesEnded(const std::vector<Touch*> &touches, Event* event);

	//���콺 �̺�Ʈ��
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event) {};
	void onMouseScroll(cocos2d::Event* event) {};

	// Ű���� �̺�Ʈ��
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	// ��ư ��ġ �̺�Ʈ��
	void skipButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void endButtonTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeOpenerTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeChangeTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void upgradeEnhanceTouch(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void debugVisibleTouch(Ref *pSender);

	// ���� ����� ȣ���ϴ� �Լ�
	void roundEnd();
	void roundChange();
	void timeSkip();
	void setRoundVariable();

	// �ݹ� �Լ�
	void monsterCreate();
	void monsterDeath();
	void explodeEffect(Vec2 point);
	void goGameOver();

	// Raycast ���� �Լ�
	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);
	void myTick(float dt);

	// ��ü ���� �Լ�
	Missile *makeMissile();
	void fireMissile();

	// UI ���� �Լ�
	void UISetting();
	void popUpCallback(Ref* pSender);
	void popUpClick();

	// ����� ���� �Լ�
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

	// 12�� ���� �ð� ǥ��
	Label* roundViewer;
	Label* timeViewer;

	// 1�� ���� ���� �� ǥ��
	Label* monsterPresentViewer;
	Label* monsterExistViewer;

	Vec2 mouse;
	std::vector<Condition*> conditionInfoArray;
	std::vector<Condition*> tempVector;
	Vector<Enemy*> enemyVector;

	DrawNode *_node;

	//�п� ���� ����
	int divisonNum;

	//Skill UI
	Vector<Sprite*> Skillboxes;
	Vector<Label*> SkillLevels;


};
#endif // __HELLOWORLD_SCENE_H__
