#include "Condition.h"

EffectCode Condition::getCode()
{
	return EffectCode::Unknown;
}

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
	conditonLevel++;
}

Condition::Condition() : conditonLevel(0) {}
Slow::Slow() : Time(5.0), code(EffectCode::Slow), deffenceReduceRate(0.7), speedReduceRate(0.5){}

float Slow::castEffect(float speed) const
{return speed*speedReduceRate;}

float Slow::castSideEffect(float defence) const
{
	if (conditonLevel < additioalLevel)
		return defence;
	else
		return defence*deffenceReduceRate;
}

EffectCode Slow::getCode()
{
	return EffectCode::Slow;
}

void Slow::enchance()
{
	conditonLevel++;
	deffenceReduceRate = deffenceReduceRate*0.7;
	speedReduceRate = speedReduceRate*0.5;
}

Knock::Knock():minusSpeed(-1000), code(EffectCode::Knock){}

float Knock::castEffect(float speed) const
{
	return minusSpeed;
}

float Knock::castSideEffect(float defence) const
{
	return 0;
}

EffectCode Knock::getCode()
{
	return code;
}

void Knock::enchance()
{
	minusSpeed -= 100;
}

PowerUp::PowerUp():rangeRate(600), pierceNum(3){}

float PowerUp::castEffect(float speed) const
{
	return rangeRate;
}

float PowerUp::castSideEffect(float defence) const
{
	return pierceNum;
}

EffectCode PowerUp::getCode()
{
	return EffectCode::PowerUp;
}

void PowerUp::enchance()
{
	rangeRate += 200;
}

Division::Division():divideNum(3){}

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
	divideNum++;
}

EffectCode Division::getCode()
{
	return EffectCode::Division;
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

EffectCode Mine::getCode()
{
	return EffectCode::Mine;
}

void Mine::enchance()
{
	holdTime += 2;
}

Explode::Explode():damage(100){}

float Explode::castEffect(float num) const
{
	return damage;
}

float Explode::castSideEffect(float num) const
{
	return 0.0f;
}

EffectCode Explode::getCode()
{
	return EffectCode::Explode;
}

void Explode::enchance()
{
	damage += 25;
}
