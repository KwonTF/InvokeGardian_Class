#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

/*
base class of extra explosion
creater : ZeroFe
*/
class Explosion : public Collisioner
{
protected:
	float removeTime;
public:
	Explosion();
	~Explosion() {};

	static Explosion* create(const std::string &filename);

	virtual void collisioned(int damage, std::vector<Condition*> &c);

	void setRemoveTime(float time);
	void removeExplosion(float f);

	void deathAnimation();
	void destroy();
};