#include "Barrier.h"

Barrier::Barrier()
{
	hp = 500;
	recovery = 0;
	maxWeight = 30;
	turretArea = 1;
}

void Barrier::setBarrierAbillity(int _hp, int _recovery, int mWeight, int tArea)
{
	hp = _hp;
	recovery = _recovery;
	maxWeight = mWeight;
	turretArea = tArea;
}

int Barrier::getHP()
{
	return hp;
}

int Barrier::getRecovery()
{
	return recovery;
}

int Barrier::getMaxWeight()
{
	return maxWeight;
}

int Barrier::getTurretArea()
{
	return turretArea;
}