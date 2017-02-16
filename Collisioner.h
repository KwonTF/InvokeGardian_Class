#pragma once
#include "cocos2d.h"
#include "Condition.h"

USING_NS_CC;

/*
base class of collisioner
creater : ZeroFe
*/
class Collisioner : public cocos2d::Sprite
{
protected:
	int attack;						// attack damage for other
	Condition *deliveryCondition;	// attack Condition Error for other
public:
	Collisioner() {};
	virtual ~Collisioner();

	static Collisioner* create(const std::string &filename);

	Condition *getCondition();
	int getAttack();
	virtual void collisioned(int damage, Condition *c);
};

