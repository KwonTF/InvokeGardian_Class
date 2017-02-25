#include "Condition.h"

EffectCode Condition::getCode()
{
	return EffectCode::Unknown;
}

float Condition::castEffect(float input) const
{
	return input;
}

void Condition::enchance()
{
	conditonLevel++;
}

Condition::Condition() : conditonLevel(0) {}
Slow::Slow() : Time(5.0), code(EffectCode::Slow), deffenceReduceRate(0.7), speedReduceRate(0.7){}

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
	deffenceReduceRate = deffenceReduceRate*0.9;
	speedReduceRate = speedReduceRate*0.6;
}