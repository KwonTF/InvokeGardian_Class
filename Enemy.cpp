#include "Enemy.h"
Enemy::Enemy()
{
	divideAmount = 0;
	isDivide = false;
}
Enemy::~Enemy()
{
}

Enemy* Enemy::create(const std::string &filename)
{
	Enemy *enemy = new (std::nothrow) Enemy();

	if (enemy && enemy->initWithFile(filename))
	{
		enemy->autorelease();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return nullptr;
}

// add type to enemy
void Enemy::typeEnhance(monsterType t)
{

}

// for divide type, add monster divide ability
void Enemy::divideEnemy()
{

}

// when create or get Condition Error, set aim to attack Tower
void Enemy::setEnemyAim(cocos2d::Vec2 &aimPos)
{

}

void Enemy::shootMissile()
{

}