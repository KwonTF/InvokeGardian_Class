#include "Unit.h"

/*
set unit image infomation
filename : file root of unit's image
fileNum : number of unit's image
*/
void Unit::setImageInfo(const std::string* filename, const int fileNum)
{
	image = new std::string[fileNum];
	for (int i = 0; i < fileNum; i++)
	{
		image[i] = filename[i];
	}
	imageNum = fileNum;
}

Unit* Unit::create(const std::string &filename)
{
	Unit *unit = new (std::nothrow) Unit();

	if (unit && unit->initWithFile(filename))
	{
		unit->autorelease();
		return unit;
	}

	CC_SAFE_DELETE(unit);
	return nullptr;
}

void Unit::collisioned(int damage, Condition *c)
{
	hpCurrent -= damage;

	if (hpCurrent > hpMax)
		hpCurrent = hpMax;

	if (hpCurrent <= 0)
		destroy();

	log("Unit collisioned : hp - %d, damage - %d", hpCurrent, damage);
}

void Unit::setHP(int HP)
{
	hpCurrent = HP;
	hpMax = HP;
}

void Unit::setAttack(int atk)
{
	attack = atk;
}

void Unit::setSpeed(float speed)
{
	speed_move = speed;
}

int Unit::getHP()
{
	return hpCurrent;
}

float Unit::getSpeed()
{
	return speed_move;
}

// make Unit's death Animation
void Unit::deathAnimation()
{
	// Particle
	Node* parentFinder;

	parentFinder = getParent();
	if (parentFinder != NULL)
	{
		// make particle and set ability
		ParticleSystem *particleSys = ParticleExplosion::create();
		particleSys->retain();

		particleSys->setTexture(Director::getInstance()->getTextureCache()->addImage("Others/Fire.png"));

		particleSys->setPosition(getPosition());
		parentFinder->addChild(particleSys);

		particleSys->setStartColor(Color4F::YELLOW);
		particleSys->setEndColor(Color4F::YELLOW);
		//particleSys->setStartColorVar(Color4F::YELLOW);
		//particleSys->setEndColorVar(Color4F::YELLOW);

		particleSys->setEmissionRate(500.0f);		// 파티클 생성률
		particleSys->setStartSize(3.0f);			// 시작 생성 크기
		particleSys->setStartSizeVar(0.0f);
		particleSys->setDuration(1.0f);				// 파티클 생성시간
		particleSys->setLife(0.3f);					// 파티클 유지시간
		particleSys->setLifeVar(0.2f);

		// invisible sprite image
		this->setOpacity(0);
	}
}

// destory unit from game
void Unit::destroy()
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	auto callback1 = CallFunc::create(CC_CALLBACK_0(Unit::deathAnimation, this));
	auto callback2 = CallFunc::create(CC_CALLBACK_0(Unit::removeFromParent, this));
	//auto sequence = Sequence::create(callback1, DelayTime::create((float)(imageNum-1)/10), callback2, nullptr);
	auto sequence = Sequence::create(callback1, DelayTime::create(1.0f), callback2, nullptr);

	runAction(sequence);
}