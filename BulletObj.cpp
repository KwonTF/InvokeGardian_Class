#include "BulletObj.h"



BulletObj::BulletObj()
{
}


BulletObj::~BulletObj()
{
}

void BulletObj::update(float input)
{
	this->setPositionX(this->getPositionX() + (x * 1000 * input));
	this->setPositionY(this->getPositionY() + (y * 1000 * input));
}

void BulletObj::pushEffects(Condition * input)
{
	EffectArray.push_back(input);
}

BulletObj* BulletObj::createAndInit(float rotation) {
	BulletObj* bullet = new BulletObj();
	bullet->initWithFile("Others/Bullet.PNG");
	bullet->autorelease();
	bullet->x = sinf(CC_DEGREES_TO_RADIANS(rotation));
	bullet->y = cosf(CC_DEGREES_TO_RADIANS(rotation));
	bullet->schedule(schedule_selector(BulletObj::update));
	return bullet;
}

int BulletObj::getArraySize()
{
	return EffectArray.size();
}

Condition* BulletObj::sendCondition(int i)
{
	return EffectArray.at(i);
}
