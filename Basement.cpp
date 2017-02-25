#include "Basement.h"


Basement::Basement():HP(500), finalAttackLevel(1)
{
}


Basement::~Basement()
{
}

Basement* Basement::createAndInit()
{
	Basement* basement = new Basement();
	basement->initWithFile("Unit/Basement.PNG");
	basement->autorelease();
	basement->setAnchorPoint(Vec2(0.5,0.5));
	return basement;
}

void Basement::getDamage(int damage)
{
	HP -= damage;
}

int Basement::getHP()
{
	return HP;
}
