#include "Mutate.h"

Mutate::Mutate() : type(0), level(1), hpPer(1.0), atkPer(1.0), rangePer(1.0), asPer(1.0), spdPer(1.0) {}
Mutate::~Mutate(){}

void Mutate::setMutateInfo(int mType, int mLevel, float mHpPer,
	float mAtkPer, float mRangePer, float mAsPer, float mSpdPer)
{
	type = mType;
	level = mLevel;

	hpPer = mHpPer;
	atkPer = mAtkPer;
	rangePer = mRangePer;
	asPer = mAsPer;
	spdPer = mSpdPer;
}

void Mutate::setImageInfo(std::string image)
{
	imageName = image;
}

Mutate& Mutate::operator=(const Mutate& mutate)
{
	type = mutate.type;
	level = mutate.level;

	hpPer = mutate.hpPer;
	atkPer = mutate.atkPer;
	rangePer = mutate.rangePer;
	asPer = mutate.asPer;
	spdPer = mutate.spdPer;

	imageName = mutate.imageName;

	return *this;
}