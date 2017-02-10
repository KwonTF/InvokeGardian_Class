#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
base class of collisioner
creater : ZeroFe
*/
class Collisioner : public cocos2d::Sprite
{
protected:

public:
	Collisioner();
	~Collisioner();

	static Collisioner* create(const std::string &filename);

	virtual void setCondition();
	virtual void getCondition();
	virtual int getAttack();
	virtual void getDamage(int damage);
};

