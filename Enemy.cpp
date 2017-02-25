#include "Enemy.h"

Enemy::Enemy()
{
	divideAmount = 0;
	isDivide = false;
	attackCoolTime = 180;
	currentCoolTime = 0;

	slowActive = false;
	slowTime = 0;
	slowRate = 1.0;

	schedule(schedule_selector(Enemy::CalculateEffect), 1.0f);
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

void Enemy::setBaseAbillity(int hp, int atk, int range, int speed, int as)
{
	hpMax = hp;
	hpCurrent = hp;
	attack = atk;
	attackRange = range;
	moveSpeed = speed;
}

// set Enemy's attack range
void Enemy::setRange(int range)
{
	attackRange = range;
}

int Enemy::getRange()
{
	return attackRange;
}

// set Enemy's PhysicsBody BitMask
void Enemy::setEnemyTeam()
{
	if (getPhysicsBody() != nullptr)
	{
		getPhysicsBody()->setCategoryBitmask(0x0C0);
		getPhysicsBody()->setContactTestBitmask(0x30C);
		getPhysicsBody()->setCollisionBitmask(0x00C);
	}
}

// if Enemy dead, callback to HelloWorld
void Enemy::setDeathCallback(void (*FucCall)())
{
	deathCallback = FucCall;
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
void Enemy::setEnemyAim(const cocos2d::Vec2 &aimPos)
{
	// 목표 설정
	destinat = aimPos;

	float diffX = destinat.x - getPositionX();
	float diffY = destinat.y - getPositionY();
	float angle = atan2f(diffY, diffX);
	angle = CC_RADIANS_TO_DEGREES(angle);
	angle = 90 - angle;
	x = sinf(CC_DEGREES_TO_RADIANS(angle));
	y = cosf(CC_DEGREES_TO_RADIANS(angle));

	cocos2d::log("%f %f", diff.x, diff.y);

	// 실행
	schedule(schedule_selector(Enemy::update));
}

void Enemy::shootMissile()
{
	Missile* missile = Missile::create("Others/Bullet.PNG");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(missile->getContentSize().width / 2, material);

	// 몸체 설정
	missile->setPhysicsBody(body);
	missile->setPosition(getPosition());
	missile->getPhysicsBody()->setVelocity(Vec2(0, missile->getSpeed()));

	// 내부 값 설정
	missile->setAttack(3);
	missile->setSpeed(300.0);
	missile->setPenetCount(1);
	missile->setRange(600);

	if (getParent() != nullptr)
	{
		getParent()->addChild(missile);
	}
}


void Enemy::CalculateEffect(float input)
{
	/*
	std::vector<Condition*>::iterator iter;
	for (iter = conditionArray.begin(); iter != conditionArray.end(); iter++) {
		switch ((*iter)->getCode())
		{
		case EffectCode::Slow:
			if ((*iter)->getTime() == 0) {
				this->moveSpeed = 50;
				//conditionArray.erase(iter);
			}
			else {
				(*iter)->ReduceTime();
				this->speed = 10;
			}
			break;
		default:
			break;
		}
	}
	*/
}

void Enemy::update(float input)
{
	diff = destinat - getPosition();
	diff = diff.getNormalized();
	setRotation(diff.getAngle() * 180 / M_PI);

	float dist;

	dist = getPosition().getDistance(destinat);
	cocos2d::log("%f", x);

	if (dist < attackRange)
	{
		currentCoolTime++;
		if (currentCoolTime > attackCoolTime) {
			shootMissile();
			currentCoolTime = 0;
		}
	}
	else
	{
		this->setPosition(this->getPosition() + diff * moveSpeed * input);
	}
}

void Enemy::destroy()
{
	Unit::destroy();


}