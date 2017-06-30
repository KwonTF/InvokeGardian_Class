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
	std::vector<Condition*> conditionArray;	// attack Condition Error for other
public:
	Collisioner() {};
	virtual ~Collisioner();
	void setCondition(std::vector<Condition*> input);
	std::vector<Condition*> &getCondition();
	int getAttack();
	virtual void collisioned(int damage, std::vector<Condition*> &c) = 0;

	// 충돌 비트마스크 설정
	static const int bitmaskZero;
	static const int bitmaskPlayerAll;
	static const int bitmaskEnemyAll;
};

