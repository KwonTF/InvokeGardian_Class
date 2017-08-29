#include "Explosion.h"

Explosion::Explosion()
	:removeTime(0.0)
{
	attack = 0;
}

Explosion* Explosion::create(const std::string &filename)
{
	Explosion *explosion = new (std::nothrow) Explosion();

	if (explosion && explosion->initWithFile(filename))
	{
		explosion->autorelease();
		return explosion;
	}

	CC_SAFE_DELETE(explosion);
	return nullptr;
}

void Explosion::make()
{
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(100 / 2, material);

	// 몸체 설정
	this->setPhysicsBody(body);
}

// explosion collsioned other collisioner, no effect for explosion(auto remove)
void Explosion::collisioned(int damage, std::vector<Condition*> &c)
{

}

// set explosion's attack point
void Explosion::setAttack(int atk)
{
	attack = atk;
}

// set explosion's remove time
void Explosion::setRemoveTime(float time)
{
	removeTime = time;
}

// make Missile's death animation
void Explosion::deathAnimation()
{
	cocos2d::log("death");

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

		particleSys->setStartColor(Color4F::ORANGE);
		particleSys->setEndColor(Color4F::ORANGE);
		particleSys->setStartColorVar(Color4F::WHITE);
		particleSys->setEndColorVar(Color4F::WHITE);

		particleSys->setEmissionRate(1500.0f);		// 파티클 생성률
		particleSys->setStartSize(3.0f);			// 시작 생성 크기
		particleSys->setStartSizeVar(0.0f);
		particleSys->setDuration(0.5f);				// 파티클 생성시간
		particleSys->setLife(0.3f);					// 파티클 유지시간
		particleSys->setLifeVar(0.2f);

		// invisible sprite image
		this->setOpacity(0);
	}
}


// remove explosion after remove time
void Explosion::removeExplosion()
{
	cocos2d::log("remove");

	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	removeFromParent();
}

void Explosion::destroy()
{
	cocos2d::log("%.0f %.0f", getPositionX(), getPositionY());

	auto callback1 = CallFunc::create(CC_CALLBACK_0(Explosion::deathAnimation, this));
	auto callback2 = CallFunc::create(CC_CALLBACK_0(Explosion::removeExplosion, this));
	auto sequence = Sequence::create(callback1, DelayTime::create(1.0f), callback2, nullptr);

	runAction(sequence);
}