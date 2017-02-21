#pragma once
#include "cocos2d.h"
#include "Basement.h"
#include "Condition.h"
USING_NS_CC;
class Enemy : public Sprite
{
private:
	Vec2 destinat;
	float x, y, slowRate;
	int attackRange, attackCoolTime, currentCoolTime, HP, moveSpeed, slowTime;
	boolean slowactive;
	Basement* Target;
	std::vector<Condition*> conditionArray;
	void CalculateEffect(float input);
	void update(float input);
public:
	static Enemy* createAndInit();
	Enemy();
	void setHP(int input);
	int getHP();
	void getCondition(Condition* input);
	void setDest(Vec2 destination);
	void setRange(int input);
	void setTarget(Basement* target);
	int getRange();
	~Enemy();
};

