#include "Missile.h"

Missile* Missile::create(const std::string &filename)
{
	Missile *missile = new (std::nothrow) Missile();

	if (missile && missile->initWithFile(filename))
	{
		missile->autorelease();
		return missile;
	}

	CC_SAFE_DELETE(missile);
	return missile;
}

// set range of Missile
void Missile::setRange(int movelimit)
{
	range = movelimit;

	scheduleOnce(schedule_selector(Missile::removeMissile), (float)range / speed);
}

/*
set Missile's bitmask
team - 0 is player team, others are enemy
*/
void Missile::setMissileTeam(int team)
{
	// no collision
	getPhysicsBody()->setCollisionBitmask(0x000);

	if (team == 0)
	{
		getPhysicsBody()->setCategoryBitmask(0x300);
		getPhysicsBody()->setContactTestBitmask(0x0F0);
	}
	else
	{
		getPhysicsBody()->setCategoryBitmask(0xC00);
		getPhysicsBody()->setContactTestBitmask(0x00F);
	}
}

void Missile::getDamage(int damage)
{
	penetrationCount--;

	if (penetrationCount <= 0)
		destroy();
}


/*
remove Missile without death animation
warning : need PhysicsBody
*/
void Missile::removeMissile(float f)
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	removeFromParent();
}

// make Missile's explosion
void Missile::deathAnimation()
{
	// Particle
	/*
	Node* parentFinder;

	parentFinder = getParent();
	if (parentFinder != NULL)
	{
	// make particle and set ability
	ParticleSystem *particleSys = ParticleExplosion::create();
	particleSys->retain();

	particleSys->setTexture(Director::getInstance()->getTextureCache()->addImage(resData::test[4]));

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
	*/
}

// destory unit from game
void Missile::destroy()
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	auto callback1 = CallFunc::create(CC_CALLBACK_0(Missile::deathAnimation, this));
	auto callback2 = CallFunc::create(CC_CALLBACK_0(Missile::removeFromParent, this));
	//auto sequence = Sequence::create(callback1, DelayTime::create((float)(imageNum-1)/10), callback2, nullptr);
	auto sequence = Sequence::create(callback1, DelayTime::create(1.0f), callback2, nullptr);

	runAction(sequence);
}