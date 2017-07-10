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

	void setMutateInfo(Mutate &mutate);
	void setImageInfo(std::string image);
};