#include "Collisioner.h"

Collisioner::~Collisioner()
{
}

int Collisioner::getAttack()
{
	return attack;
}

Condition* Collisioner::getCondition()
{
	return deliveryCondition;
}