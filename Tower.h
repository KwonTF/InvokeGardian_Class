#pragma once
#include "cocos2d.h"
#include "Unit.h"
#include "Turret.h"
#include "Barrier.h"

typedef std::function<void()> gameoverCallback;

class Tower : public Unit
{
// 변수 목록
private:
	gameoverCallback deathCallback;
public:
	Tower();
	~Tower() {};

	static Tower* create(const std::string &filename);

	void healTower(const int heal);
	
	void destroy() override;

	void setDeathCallback(const gameoverCallback &callback);
};