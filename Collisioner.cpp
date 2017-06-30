#include "Collisioner.h"

const int Collisioner::bitmaskZero = 0x00000000;
const int Collisioner::bitmaskPlayerAll = 0x00000000;
const int Collisioner::bitmaskEnemyAll = 0x00000000;

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