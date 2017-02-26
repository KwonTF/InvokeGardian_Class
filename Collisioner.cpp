#include "Collisioner.h"

Collisioner::~Collisioner()
{
	conditionArray.clear();
}

int Collisioner::getAttack()
{
	return attack;
}

std::vector<Condition> &Collisioner::getCondition()
{
	return conditionArray;
}