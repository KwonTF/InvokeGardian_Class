#include "Condition.h"
EffectCode Condition::getCode()
{
	return EffectCode();
}
float Condition::castEffect(float input) const
{
	return 0.0f;
}
void Condition::enchance()
{
}
Condition::Condition() : conditonLevel(0) {}
Condition::~Condition()
{
}
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
{return EffectCode::Slow;}

void Slow::enchance()
{conditonLevel++;
deffenceReduceRate = 0.6;
speedReduceRate = 0.6;
}
