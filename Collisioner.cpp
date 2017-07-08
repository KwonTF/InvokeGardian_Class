#include "Collisioner.h"

const int Collisioner::bitmaskZero = 0x00000000;
const int Collisioner::bitmaskPlayerAll = 0x00000000;
const int Collisioner::bitmaskEnemyAll = 0x00000000;

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

std::vector<Condition*> &Collisioner::getCondition()
{
	return conditionArray;
}