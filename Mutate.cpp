#include "Mutate.h"

Mutate::Mutate()
{

}

Mutate::~Mutate()
{

}

void Mutate::setMutateInfo(int mType, int mLevel)
{
	type = mType;
	level = mLevel;
}

void Mutate::setImageInfo(std::string image)
{
	imageName = image;
}

const int Mutate::getType()
{
	return type;
}

const int Mutate::getLevel()
{
	return level;
}

const float Mutate::getHpPer()
{
	return hpPer;
}

const float Mutate::getAtkPer()
{
	return atkPer;
}

const float Mutate::getAsPer()
{
	return asPer;
}

const float Mutate::getSpdPer()
{
	return spdPer;
}