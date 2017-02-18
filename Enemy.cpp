#include "Enemy.h"
Enemy * Enemy::createAndInit()
{
	Enemy* enemy = new Enemy();
	//enemy->setHP(100);
	//enemy->setAttack(10);
	//enemy->setSpeed(50);
	enemy->initWithFile("Unit/Hostile.png");
	enemy->autorelease();
	enemy->setRange(200);
	enemy->setHP(100);
	return enemy;
}
Enemy::Enemy():attackCoolTime(180), currentCoolTime(0)
{
}
void Enemy::setHP(int input)
{
	HP = input;
}
int Enemy::getHP()
{
	return HP;
}
void Enemy::update(float input)
{
	if (sqrtf(((this->getPositionX() - destinat.x)*(this->getPositionX() - destinat.x)) + ((this->getPositionY() - destinat.y)*(this->getPositionY() - destinat.y)))<attackRange) {
		currentCoolTime++;
		if (currentCoolTime > attackCoolTime) {
			Target->getDamage(10);
			currentCoolTime = 0;
		}
	}
	else {
		this->setPositionX(this->getPositionX() + (x * 50 * input));
		this->setPositionY(this->getPositionY() + (y * 50 * input));
	}
}
void Enemy::setDest(Vec2 destination)
{
	destinat = destination;
	float diffX = destination.x - getPositionX();
	float diffY = destination.y - getPositionY();
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle);
	angle = 90 - angle;
	x = sinf(CC_DEGREES_TO_RADIANS(angle));
	y = cosf(CC_DEGREES_TO_RADIANS(angle));
	schedule(schedule_selector(Enemy::update));
}
void Enemy::setRange(int input)
{
	attackRange = input;
}
void Enemy::setTarget(Basement * target)
{
	Target = target;
	setDest(target->getPosition());
}
int Enemy::getRange()
{
	return attackRange;
}
Enemy::~Enemy()
{
}
