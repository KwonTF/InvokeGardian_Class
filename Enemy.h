#pragma once
#include "cocos2d.h"
#include "Basement.h"
USING_NS_CC;
class Enemy : public Sprite
{
private:
	Vec2 destinat;
	float x, y;
	int attackRange, attackCoolTime, currentCoolTime, HP;
	Basement* Target;
public:
	static Enemy* createAndInit();
	Enemy();
	void setHP(int input);
	int getHP();
	void update(float input);
	void setDest(Vec2 destination);
	void setRange(int input);
	void setTarget(Basement* target);
	int getRange();
	~Enemy();
};

