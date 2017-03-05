#pragma once
#include "cocos2d.h"
#include "Unit.h"
#include "Missile.h"

typedef std::function<void()> monsterCallback;

namespace mutate {
	extern const int Range[6];
	extern const float HP[6];
	extern const float Attack[6];
	extern const float Speed[6];
	extern const float AtkSpeed[6];
};

/*
class of enemy object
create by ZeroFe
*/
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
	//슬로우 변수
	float slowRate;
	int slowTime;
	boolean slowActive;
	//넉백 변수
	float knockBackSpeed;

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
	void typeEnhance(int monsterType);
	void divideEnemy();
	void setEnemyAim(const cocos2d::Vec2 &aimPos);
	void shootMissile();

	virtual void destroy();

private:
	void update(float input);
	//효과 관련 함수
	void slowTimeReduce(float input);
	void CalculateEffect(float input);
	void KnockBack(float input);
};

