#pragma once
#include <string>

/*
���� ���� Ŭ����
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