#pragma once
#include "cocos2d.h"
#include "Unit.h"

class Tower : public Unit
{
// 변수 목록
private:
	unitCallback deathCallback;

public:
	Tower();
	~Tower() {};

	static Tower* create(const std::string &filename);

	void healTower(const int heal);
	
	void destroy() override;

	void setDeathCallback(const unitCallback &callback);
};