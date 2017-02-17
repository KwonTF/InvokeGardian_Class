#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

/*
base class of Missile
creater : ZeroFe
*/
class Missile : public Collisioner
{
protected:
	// 유닛에 필요한 이미지
	std::string *image;
	int imageNum;

	// 이동속도
	float speed;

	int range;				// 사거리 제한
	int penetrationCount;	// 관통 가능한 유닛 수
	int divideCount;		// 분열 수

public:
	Missile() {};
	~Missile() {};

	static Missile* create(const std::string &filename);

	void collisioned(int damage, Condition *c);

	// set ability
	void setAttack(int atk);

	void setSpeed(int s);
	void setRange(int movelimit);
	void setPenetCount(int count);
	void setDivideCount(int count);

	void setMissileTeam(int team);

	float getSpeed();

	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};

