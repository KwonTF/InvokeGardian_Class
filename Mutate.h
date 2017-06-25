#pragma once
#include <string>

/*
���� ���� Ŭ����
create by ZeroFe
*/
class Mutate {
private:
	int type;
	int level;

	float hpPer;
	float atkPer;
	float asPer;
	float spdPer;

	std::string imageName;
public:
	Mutate();
	~Mutate();

	void setMutateInfo(int mType, int mLevel);
	void setImageInfo(std::string image);

	const int getType();
	const int getLevel();

	const float getHpPer();
	const float getAtkPer();
	const float getAsPer();
	const float getSpdPer();
};