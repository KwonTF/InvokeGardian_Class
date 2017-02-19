#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

/*
base class of game unit
create by ZeroFe
*/
class Unit : public Collisioner
{
protected:
	// 유닛에 필요한 이미지
	std::string *image;
	int imageNum;

	// 체력
	int hpCurrent;
	int hpMax;

	// 이동속도
	float speed_move;

public:
	Unit() {};
	~Unit() {};

	static Unit* create(const std::string &filename);

	virtual void collisioned(int damage, Condition *c);

	void setImageInfo(const std::string *filename, const int fileNum);

	// set ability
	void setHP(int hp);
	void setAttack(int atk);
	void setSpeed(float spd);

	// get ability
	int getHP();
	float getSpeed();

	// remove object
	void deathAnimation();
	void destroy();
};

