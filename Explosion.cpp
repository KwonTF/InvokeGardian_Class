#include "Explosion.h"

Explosion::Explosion()
{
	attack = 0;
	removeTime = 0.5;

	scheduleOnce(schedule_selector(Explosion::removeExplosion), removeTime);
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

	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, material);

	// ¸öÃ¼ ¼³Á¤
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

// remove explosion after remove time
void Explosion::removeExplosion(float f)
{
	cocos2d::log("%.0f %.0f", getPositionX(), getPositionY());

	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	removeFromParent();
}