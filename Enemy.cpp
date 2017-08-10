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

/*
// �ش� ��ü�� PhysicsBody ����
// Bitmask, ��ġ ���� ���� �����������
void Enemy::make()
{
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createBox(this->getContentSize(), material);

	this->setPhysicsBody(body);
	this->getPhysicsBody()->setDynamic(false);
	//monster->setPhysicsBitmask(Collisioner::bitmaskEnemyAll, ~(Collisioner::bitmaskBulletTwo + Collisioner::bitmaskEnemyAll), Collisioner::bitmaskPlayerAll);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//monster->setPosition(Vec2(_winSize.width * (rand() % 2), (rand() % static_cast<int>(_winSize.height))));
}
*/

void Enemy::setBaseAbillity(int hp, int atk, int range, int speed, int as)
{
	hpMax = hp;
	hpCurrent = hp;
	attack = atk;
	attackRange = range;
	moveSpeed = speed;
}

// add type to enemy
// 0 : normal, 1 : range, 2 : mass, 3 : divide, 4 : golem, 5 : faster
void Enemy::typeEnhance(Mutate mutateInfo)
{
	// �ɷ�ġ ��ȭ
	hpMax = static_cast<int>(hpMax * mutate.hpPer);
	hpCurrent = static_cast<int>(hpCurrent * mutate.hpPer);
	attackRange = static_cast<int>(attackRange * mutate.rangePer);
	attack = static_cast<int>(attack * mutate.atkPer);
	moveSpeed = moveSpeed * mutate.spdPer;
	attackCoolTime = static_cast<int>(attackCoolTime * mutate.asPer);

	// ��� �߰�
	// 1. range type : ��Ÿ� �߰� - �ɷ�ġ ��ȭ���� �ذ�
	// 2. mass type : ���� ���� ���� - ���� ������ �޾Ƽ� ����Լ��� �ֺ� ��ġ�� �����ϰ� ��
	if (mutate.type == 2)
	{
		Vec2 pos = getPosition();
		for (int i = 0; i < mutate.level + 1; i++)
		{

		}
	}
	// 3. divide type : ������ ���͸� ���� �����ϴ� �Լ� �߰�
	else if (mutate.type == 3)
	{

	}
	// 4. golem type : �ɷ�ġ ��ȭ���� �ذ�
	// 5. faster type : �ܻ�ȿ���� �������ֱ�
	else if (mutate.type == 5)
	{
		projectImage(mutate.imageName);
	}
}

// for divide type, add monster divide ability
void Enemy::divideEnemy()
{

}

// when create or get Condition Error, set aim to attack Tower
void Enemy::setEnemyAim(const cocos2d::Vec2 &aimPos)
{
	// ��ǥ ����
	destinat = aimPos;

	// ����
	schedule(schedule_selector(Enemy::update));
}

void Enemy::shootMissile()
{
	Missile* missile = Missile::create("Others/Bullet.PNG");

	// ���� �� ����
	missile->setAttack(attack);
	missile->setSpeed(300.0);
	missile->setPenetCount(1);
	missile->setRange(600);
	missile->setColor(Color3B::RED);

	// ��ü ����
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(missile->getContentSize().width / 2, material);

	missile->setPhysicsBody(body);
	missile->setPosition(getPosition());
	missile->getPhysicsBody()->setVelocity(diff * missile->getSpeed());
	missile->setPhysicsBitmask(Collisioner::bitmaskBulletTwo, ~(Collisioner::bitmaskBulletAll + Collisioner::bitmaskEnemyAll), Collisioner::bitmaskZero);
	

	// ���ӿ� �߰�
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
