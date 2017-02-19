#pragma once
#include "cocos2d.h"
#include "Unit.h"

class Tower : public Unit
{
// 변수 목록
private:
	// 구조물 기반 부분
	int hpRegen;
	int maxWeight;
	int turretArea;

	// 포탑 부분
	
	// 수호석 부분

public:
	Tower() {};
	~Tower() {};

	static Tower* create(const std::string &filename);
};

class Turret
{
friend class Tower;

private:
	int id;
	std::string name;

	int attack;
	int attackSpeed;

	int weight;

	// 발사하는 미사일 정보
};