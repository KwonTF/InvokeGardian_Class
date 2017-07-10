#include "Mutate.h"

Mutate::Mutate()
{
	type = 0;
	level = 1;

	hpPer = 1.0;
	atkPer = 1.0;
	rangePer = 1.0;
	asPer = 1.0;
	spdPer = 1.0;
}

Mutate::~Mutate()
{

}

void Mutate::setMutateInfo(Mutate &mutate)
{
	type = mutate.type;
	level = mutate.level;

	hpPer = mutate.hpPer;
	atkPer = mutate.atkPer;
	rangePer = mutate.rangePer;
	asPer = mutate.asPer;
	spdPer = mutate.spdPer;
}

void Mutate::setImageInfo(std::string image)
{
	imageName = image;
}