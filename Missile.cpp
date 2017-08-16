#include "Missile.h"

Missile::Missile()
	: speed(400.0), range(200),
	penetrationCount(1), divideCount(0),
	isExplode(false), explodeDamage(30),
	removeTime(0.1){}

Missile* Missile::create(const std::string &filename)
{
	Missile *missile = new (std::nothrow) Missile();

	if (missile && missile->initWithFile(filename))
	{
		missile->autorelease();
		return missile;
	}

	CC_SAFE_DELETE(missile);
	return nullptr;
}

void Missile::make()
{
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, material);

	// 몸체 설정
	this->setPhysicsBody(body);
}

// if Missile collisioned
void Missile::collisioned(int damage, std::vector<Condition*> &c)
{
	penetrationCount--;

	if(isExplode)
		makeExplosion();

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

//미사일 요소 적용 함수
void Missile::castEffect()
{
	std::vector<Condition*>::iterator iter;
	for (iter = conditionArray.begin(); iter != conditionArray.end(); iter++) {
		switch ((*iter)->getCode())
		{
		case EffectCode::PowerUp:
			range += (*iter)->castEffect(range);
			if ((*iter)->conditionLevel > 6) {
				penetrationCount += (*iter)->castSideEffect(penetrationCount);
			}
			break;
		case EffectCode::Division:
			break;
		case EffectCode::Explode:
			if ((*iter)->getCode() == EffectCode::Explode) {
				isExplode = true;
				explodeDamage = 30;
			}
			break;
		case EffectCode::Mine:
			getPhysicsBody()->setVelocity(Vec2(0,0));
			range += (*iter)->castEffect(range)*speed;
			break;
		default:
			break;
		}
	}
	scheduleOnce(schedule_selector(Missile::removeMissile), (float)range / speed);
}

void Missile::makeExplosion()
{
	Explosion* explosion = Explosion::create("UI/SkillBox.PNG");

	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(explosion->getContentSize().width / 2, material);

	// 몸체 설정
	explosion->setPhysicsBody(body);
	explosion->getPhysicsBody()->setCollisionBitmask(Collisioner::bitmaskZero);
	explosion->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	explosion->setPosition(this->getPosition());

	if (this != nullptr)
		cocos2d::log("pos : %.1f %.1f", explosion->getPositionX(), explosion->getPositionY());

	// 내부 값 설정
	explosion->setAttack(explodeDamage);

	if (getParent() != nullptr)
	{
		getParent()->addChild(explosion);
	}
}

// make Missile's death animation
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