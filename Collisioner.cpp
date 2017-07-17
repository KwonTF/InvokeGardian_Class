#include "Collisioner.h"

const int Collisioner::bitmaskZero = 0x00000000;
const int Collisioner::bitmaskPlayerAll = 0x0000FF00;
const int Collisioner::bitmaskPlayerGround = 0x00000F00;
const int Collisioner::bitmaskPlayerAir = 0x0000F000;
const int Collisioner::bitmaskEnemyAll = 0x000000FF;
const int Collisioner::bitmaskEnemyGround = 0x0000000F;
const int Collisioner::bitmaskEnemyAir = 0x000000F0;
const int Collisioner::bitmaskBulletAll = 0x00FF0000;
const int Collisioner::bitmaskBulletOne = 0x00F00000;
const int Collisioner::bitmaskBulletTwo = 0x000F0000;

Collisioner::Collisioner()
{
	attack = 0;
}

Collisioner::~Collisioner()
{
	conditionArray.clear();
}

void Collisioner::setCondition(std::vector<Condition*> input)
{
	conditionArray = input;
}

void Collisioner::setPhysicsBitmask(const int categoryBitmask, const int contactBitmask, const int collisionBitmask)
{
	if (getPhysicsBody() == nullptr)
	{
		cocos2d::log("not setting Physics Bitmask");
		return;
	}

	getPhysicsBody()->setCategoryBitmask(categoryBitmask);
	getPhysicsBody()->setContactTestBitmask(contactBitmask);
	getPhysicsBody()->setCollisionBitmask(collisionBitmask);
}