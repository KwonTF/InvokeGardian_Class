#include "Collisioner.h"

Collisioner::~Collisioner()
{
	conditionArray.clear();
}

void Collisioner::setCondition(std::vector<Condition*> input)
{
	conditionArray = input;
}

int Collisioner::getAttack()
{
	return attack;
}

std::vector<Condition*> &Collisioner::getCondition()
{
	return conditionArray;
}