#pragma once
#include "cocos2d.h"
#include "Unit.h"
#include "Missile.h"

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

typedef std::function<void()> monsterCallback;

class Enemy : public Unit
{
private:
	// 분열 관련
	int divideAmount;
	bool isDivide;

	// 타워 공격
	Vec2 destinat;
	float x, y;
	Vec2 diff;

	int attackRange;
	int attackCoolTime, currentCoolTime;

	float slowRate;
	int slowTime;
	boolean slowActive;

	monsterCallback deathCallback;
public:
	Enemy();
	~Enemy();

	static Enemy* create(const std::string &filename);

	void setBaseAbillity(int hp, int attack, int range, int speed, int as);
	void setRange(int range);
	int getRange();

	void setEnemyTeam();
	void setDeathCallback(const monsterCallback &callback);
	void typeEnhance(monsterType t);
	void divideEnemy();
	void setEnemyAim(const cocos2d::Vec2 &aimPos);
	void shootMissile();

	virtual void destroy();
private:
	void CalculateEffect(float input);
	void update(float input);
};

