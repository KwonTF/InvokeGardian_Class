#pragma once
#include "cocos2d.h"
#include "Unit.h"
#include "Turret.h"
#include "Barrier.h"

class Tower : public Unit
{
// ���� ���
private:


public:
	Tower();
	~Tower() {};

	static Tower* create(const std::string &filename);
	

};