#pragma once
#include "cocos2d.h"
#include "Unit.h"

/*
class of enemy object
create by ZeroFe
*/
enum class monsterType
{
	range, mass, divide, golem, faster
};

class Enemy : public Unit
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(const std::string &filename);

	void typeEnhance(monsterType t);
};

