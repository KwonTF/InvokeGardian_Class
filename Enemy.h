#pragma once
#include "cocos2d.h"
#include "Unit.h"

/*
class of enemy object
create by ZeroFe
*/
enum class monsterType
{
	range, mass, divide, golem, faster
};

enum class monsterState
{
	move, error, attack
};

class Enemy : public Unit
{
private:
	// 분열 관련
	int divideAmount;
	bool isDivide;

public:
	Enemy();
	~Enemy();

	static Enemy* create(const std::string &filename);

	void typeEnhance(monsterType t);
	void divideEnemy();
	void setEnemyAim(cocos2d::Vec2 &aimPos);
	void shootMissile();
};

