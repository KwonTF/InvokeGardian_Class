#include "Tower.h"

Tower::Tower()
{
	hpCurrent = 500;
	hpMax = 500;
}

Tower* Tower::create(const std::string &filename)
{
	Tower *tower = new (std::nothrow) Tower();

	if (tower && tower->initWithFile(filename))
	{
		tower->autorelease();
		return tower;
	}

	CC_SAFE_DELETE(tower);
	return nullptr;
}

void Tower::healTower(const int heal)
{
	if (hpCurrent + heal > hpMax)
		hpCurrent = hpMax;
	else
		hpCurrent += heal;
}

void Tower::destroy()
{
	Unit::destroy();

	deathCallback();
}

void Tower::setDeathCallback(const gameoverCallback &callback)
{
	deathCallback = callback;
}