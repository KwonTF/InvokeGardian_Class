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

// explosion collsioned other collisioner, no effect for explosion(auto remove)
void Explosion::collisioned(int damage, std::vector<Condition*> &c)
{

}

void Explosion::setRemoveTime(float time)
{

}

// 
void Explosion::removeExplosion(float f)
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	removeFromParent();
}