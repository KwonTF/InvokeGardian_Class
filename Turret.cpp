#include "Turret.h"

Turret::Turret()
{
	rad = 0;

	schedule(schedule_selector(Turret::checkEnemy));
	schedule(schedule_selector(Turret::attackCharge));
}

void Turret::setID(int _id)
{
	id = _id;
}

void Turret::setTurretAbillity(int atk, int atkSpeed, int _weight)
{
	attack = atk;
	attackSpeed = atkSpeed;
	weight = _weight;
}

int Turret::getAttack()
{
	return attack;
}

int Turret::getAttackSpeed()
{
	return attackSpeed;
}

int Turret::getWeight()
{
	return weight;
}

bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data)
{
	*((Vec2*)data) = info.contact;

	PhysicsBody* body = info.shape->getBody();

	return false;
}

void Turret::checkEnemy(float dt)
{

}

void Turret::attackCharge(float dt)
{

}

// explosion collsioned other collisioner, no effect for explosion(auto remove)
void Turret::collisioned(int damage, std::vector<Condition*> &c)
{

}