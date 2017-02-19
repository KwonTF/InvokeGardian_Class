#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

/*
base class of game unit
create by ZeroFe
*/
class Unit : public Collisioner
{
protected:
	// ���ֿ� �ʿ��� �̹���
	std::string *image;
	int imageNum;

	// ü��
	int hpCurrent;
	int hpMax;

	// �̵��ӵ�
	float speed_move;

public:
	Unit() {};
	~Unit() {};

	static Unit* create(const std::string &filename);

	virtual void collisioned(int damage, Condition *c);

	void setImageInfo(const std::string *filename, const int fileNum);

	// set ability
	void setHP(int hp);
	void setAttack(int atk);
	void setSpeed(float spd);

	// get ability
	int getHP();
	float getSpeed();

	// remove object
	void deathAnimation();
	void destroy();
};

