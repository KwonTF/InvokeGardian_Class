#include "Enemy.h"

Enemy::Enemy()
{
	attackCoolTime = 180;
	currentCoolTime = 0;

	slowActive = false;
	slowTime = 0;
	slowRate = 1.0;

	schedule(schedule_selector(Enemy::CalculateEffect));
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
void Enemy::setDeathCallback(const monsterCallback &callback)
{
	deathCallback = callback;
}

void Enemy::setExplodeCallback(const ExplodeCallback & callback)
{
	explodeCallback = callback;
}

// add type to enemy
// 0 : normal, 1 : range, 2 : mass, 3 : divide, 4 : golem, 5 : faster
void Enemy::typeEnhance(Mutate mutateInfo)
{
	// 능력치 변화
	hpMax = (int)(hpMax * mutate.getHpPer());
	hpCurrent = (int)(hpCurrent * mutate.getHpPer());
	//attackRange += mutate::Range[monsterType];
	attack = (int)(attack * mutate.getAtkPer());
	moveSpeed = moveSpeed * mutate.getSpdPer();
	attackCoolTime = (int)(attackCoolTime * mutate.getAsPer());

	// 기능 추가
	// 1. range type : 사거리 추가 - 능력치 변화에서 해결
	// 2. mass type : 여러 마리 생성 - 유닛 포지션 받아서 재귀함수로 주변 위치에 생성하게 함
	// 3. divide type : 죽으면 몬스터를 새로 생성하는 함수 추가
	// 4. golem type : 능력치 변화에서 해결
	// 5. faster type : 잔상효과만 적용해주기
}

void Enemy::setMassType()
{

}

void Enemy::setDivideType()
{

}

void Enemy::setFasterType()
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

	// 실행
	schedule(schedule_selector(Enemy::update));
}

void Enemy::shootMissile()
{
	Missile* missile = Missile::create("Others/Bullet.PNG");

	// 내부 값 설정
	missile->setAttack(attack);
	missile->setSpeed(300.0);
	missile->setPenetCount(1);
	missile->setRange(600);
	missile->setColor(Color3B(250, 0, 0));

	// 몸체 설정
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(missile->getContentSize().width / 2, material);

	missile->setPhysicsBody(body);
	missile->setPosition(getPosition());
	missile->getPhysicsBody()->setVelocity(diff * missile->getSpeed());
	missile->setMissileTeam(1);
	

	// 게임에 추가
	if (getParent() != nullptr)
	{
		getParent()->addChild(missile);
	}
}


void Enemy::slowTimeReduce(float input)
{
	slowTime--;
}

void Enemy::CalculateEffect(float input)
{
	std::vector<Condition*>::iterator iter;
	for (iter = conditionArray.begin(); iter != conditionArray.end(); iter++) {
		switch ((*iter)->getCode())
		{
		case EffectCode::Slow:
			if (slowActive == false) {
				slowActive = true;
				slowTime += 5;
				slowRate = (*iter)->castEffect(1);
				moveSpeed = (*iter)->castEffect(moveSpeed);
				schedule(schedule_selector(Enemy::slowTimeReduce), 1.0f);
			}
			else if (slowActive == true) {
				slowTime += 5;
				moveSpeed = moveSpeed / slowRate;
				slowRate = (*iter)->castEffect(1);
				moveSpeed = (*iter)->castEffect(moveSpeed);
			}
			break;
		case EffectCode::Knock:
			if ((*iter)->castEffect(0) > knockBackSpeed) {
				knockBackSpeed = (*iter)->castEffect(0);
			}
			schedule(schedule_selector(Enemy::KnockBack),0,10,0);
			break;
		case EffectCode::Explode:
	//		explodeCallback(getPosition());
			break;
		default:
			break;
		}
	}
	conditionArray.clear();
	if (slowTime <= 0) {
		unschedule(schedule_selector(Enemy::slowTimeReduce));
		slowTime = 0;
		moveSpeed = moveSpeed / slowRate;
		slowRate = 1;
		slowActive = false;
	}
}

void Enemy::KnockBack(float input)
{
	/*
	if (getPositionX() > 960 || getPositionX() < 0 || getPositionY() < 0 || getPositionY() > 640) {
		return;
	}
	*/
	this->setPosition(this->getPosition() + diff * knockBackSpeed * input);
}

void Enemy::update(float input)
{
	diff = destinat - getPosition();
	diff = diff.getNormalized();
	setRotation(-diff.getAngle() * 180 / M_PI);

	float dist;

	dist = getPosition().getDistance(destinat);

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

	deathCallback();
}

bool Enemy::isInRange(Vec2 point, float distance)
{
	return distance >= getPosition().getDistance(point);
}
