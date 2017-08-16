#include "Condition.h"

Condition::Condition() : conditionLevel(0), elementDamage(0) {}
Condition::Condition(const Condition &rhs)
	: elementDamage(rhs.elementDamage), conditionLevel(rhs.conditionLevel) {}

float Condition::castEffect(float input) const
{
	return input;
}

float Condition::castSideEffect(float input) const
{
	return input;
}

void Condition::enchance()
{
	conditionLevel++;
}


Slow::Slow() 
	: Time(5.0), deffenceReduceRate(0.7), speedReduceRate(0.5)
{
	elementDamage = 10;
}

Slow::Slow(const Slow &rhs)
	: Condition(rhs), speedReduceRate(rhs.speedReduceRate), deffenceReduceRate(rhs.deffenceReduceRate){}

float Slow::castEffect(float speed) const
{return speed*speedReduceRate;}

float Slow::castSideEffect(float defence) const
{
	return (conditionLevel < additioalLevel) ? defence : defence * deffenceReduceRate;
}

void Slow::enchance()
{
	Condition::enchance();
	deffenceReduceRate = deffenceReduceRate*0.7;
	speedReduceRate = speedReduceRate*0.5;
}


Knock::Knock()
	:minusSpeed(-1000), stunTime(0) 
{
	elementDamage = 20;
}
Knock::Knock(const Knock &rhs)
	: Condition(rhs), minusSpeed(rhs.minusSpeed), stunTime(rhs.stunTime) {}

float Knock::castEffect(float speed) const
{
	return minusSpeed;
}

float Knock::castSideEffect(float defence) const
{
	return stunTime;
}

void Knock::enchance()
{
	Condition::enchance();
	minusSpeed -= 100;
}


PowerUp::PowerUp()
	:rangeRate(600), pierceNum(3)
{
	elementDamage = 25;
}
PowerUp::PowerUp(const PowerUp &rhs)
	: Condition(rhs), rangeRate(rhs.rangeRate), pierceNum(rhs.pierceNum) {}

float PowerUp::castEffect(float speed) const
{
	return rangeRate;
}

float PowerUp::castSideEffect(float defence) const
{
	return pierceNum;
}

void PowerUp::enchance()
{
	Condition::enchance();
	rangeRate += 200;
}


Division::Division()
	:divideNum(3)
{
	elementDamage = 0;
}
Division::Division(const Division &rhs)
	: Condition(rhs), divideNum(rhs.divideNum) {}

float Division::castEffect(float num) const
{
	return divideNum;
}

float Division::castSideEffect(float num) const
{
	return 0;
}

void Division::enchance()
{
	Condition::enchance();
	divideNum++;
}


Mine::Mine():holdTime(3){}

float Mine::castEffect(float num) const
{
	return holdTime;
}

float Mine::castSideEffect(float num) const
{
	return 0.0f;
}

void Mine::enchance()
{
	Condition::enchance();
	holdTime += 2;
}


Explode::Explode() 
	:explodeRadius(75), burnDamage(0) 
{
	elementDamage = 5;
}
Explode::Explode(const Explode &rhs)
	: Condition(rhs), explodeRadius(rhs.explodeRadius), burnDamage(rhs.burnDamage) {}

float Explode::castEffect(float num) const
{
	return explodeRadius;
}

float Explode::castSideEffect(float num) const
{
	return 0.0f;
}

void Explode::enchance()
{
	Condition::enchance();
	explodeRadius += 25;
}
