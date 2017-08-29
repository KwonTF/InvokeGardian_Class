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
	: Time(5.0f), deffenceReduceRate(0.7f), speedReduceRate(0.5f)
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

	elementDamage += 5;

	if (conditionLevel % 2 == 0)
		speedReduceRate *= 0.7f;

	if (conditionLevel % 3 == 0)
		deffenceReduceRate *= 0.7f;
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

	elementDamage += 8;

	if (conditionLevel % 2 == 0)
		stunTime++;

	if (conditionLevel % 3 == 0)
		minusSpeed -= 500;
}


PowerUp::PowerUp()
	:rangeRate(400), pierceNum(0)
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

	elementDamage += 10;

	if (conditionLevel % 2 == 0)
		pierceNum++;

	if (conditionLevel % 3 == 0)
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

	elementDamage += 1;

	/*
	if (conditionLevel % 2 == 0)
		;
	*/

	if (conditionLevel % 3 == 0)
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

	elementDamage += 1;
	/*
	if (conditionLevel % 2 == 0)
		;
	*/

	if (conditionLevel % 3 == 0)
		holdTime++;
}


Explode::Explode() 
	:explodeRadius(50), burnDamage(0) 
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

	elementDamage += 5;

	if (conditionLevel % 2 == 0)
		burnDamage += 20;

	if (conditionLevel % 3 == 0)
		explodeRadius += 25;
}
