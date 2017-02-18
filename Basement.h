#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Basement : public Sprite
{
private:
	unsigned int finalAttackLevel;
	int HP;
public:
	static Basement* createAndInit();
	void getDamage(int damage);
	int getHP();
	Basement();
	~Basement();
};

