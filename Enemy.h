#pragma once
#include "cocos2d.h"
#include "Unit.h"
#include "Missile.h"
#include "Mutate.h"

typedef std::function<void(Vec2)> ExplodeCallback;

/*
class of enemy object
create by ZeroFe
*/
class Enemy : public Unit
{
private:
	// ���� ����
	Mutate mutate;

	// Ÿ�� ����
	Vec2 destinat;
	float x, y;
	Vec2 diff;

	int attackRange;
	int attackCoolTime, currentCoolTime;

	//���ο� ����
	float slowRate;
	int slowTime;
	bool slowActive;

	//�˹� ����
	float knockBackSpeed;

	unitCallback createCallback;
	unitCallback deathCallback;
	unitCallback divideCallback;
	ExplodeCallback explodeCallback;
public:
	Enemy();
	~Enemy();

	static Enemy* create(const std::string &filename);

	//void make() override;

	void setBaseAbillity(int hp, int attack, int range, int speed, int as);
	inline void setRange(const int range){ attackRange = range; }

	inline int getRange() { return attackRange; }

	inline void setCreateCallback(const unitCallback &callback) { createCallback = callback; createCallback(); }
	inline void setDeathCallback(const unitCallback &callback) {deathCallback = callback;}
	void setExplodeCallback(const ExplodeCallback &callback) = delete;

	// ���� ���� �Լ�
	void typeEnhance(Mutate mutateInfo);

	// ���� ���� �Լ�
	void setEnemyAim(const cocos2d::Vec2 &aimPos);
	void shootMissile();

	// ���� ���� �Լ�
	virtual void destroy() override;
	bool isInRange(Vec2 point, float distance);
private:
	void update(float input);
	//ȿ�� ���� �Լ�
	void slowTimeReduce(float input);
	void CalculateEffect(float input);
	void KnockBack(float input);

	void divideEnemy();
};