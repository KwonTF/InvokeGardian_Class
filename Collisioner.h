#pragma once
#include "cocos2d.h"
#include "Condition.h"
#include "MathCalculator.h"

USING_NS_CC;

/*
base class of collisioner
creater : ZeroFe
*/
class Collisioner : public cocos2d::Sprite
{
protected:
	int attack;								// attack damage for other
	std::vector<Condition*> conditionArray;	// attack Condition Error for other
public:
	Collisioner();
	virtual ~Collisioner();

	virtual void make();

	void setCondition(std::vector<Condition*> input);
	void setPhysicsBitmask(const int categoryBitmask, const int contactBitmask, const int collisionBitmask);

	inline std::vector<Condition*> &getCondition() { return conditionArray; }
	inline int getAttack() { return attack; }
	virtual void collisioned(int damage, std::vector<Condition*> &c) = 0;

	// 충돌 비트마스크 설정
	static const int bitmaskZero;
	static const int bitmaskPlayerAll;
	static const int bitmaskPlayerGround;
	static const int bitmaskPlayerAir;
	static const int bitmaskEnemyAll;
	static const int bitmaskEnemyGround;
	static const int bitmaskEnemyAir;
	static const int bitmaskBulletAll;
	static const int bitmaskBulletOne;
	static const int bitmaskBulletTwo;
};

