#pragma once
#include <string>

/*
변이 정보 클래스
create by ZeroFe
*/
class Mutate {
public:
	int type;
	int level;

	float hpPer;
	float atkPer;
	float rangePer;
	float asPer;
	float spdPer;

	std::string imageName;
public:
	Mutate();
	~Mutate();

	void setMutateInfo(int mType, int mLevel, float mHpPer, 
		float mAtkPer, float mRangePer, float mAsPer, float mSpdPer);
	void setImageInfo(std::string image);
	Mutate& operator =(const Mutate& mutate);
};