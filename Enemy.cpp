#include "Enemy.h"
Enemy::Enemy()
{
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