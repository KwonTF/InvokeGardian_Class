#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

/*
base class of Missile
creater : ZeroFe
*/
class Missile : public Collisioner
{
protected:
	// ���ֿ� �ʿ��� �̹���
	std::string *image;
	int imageNum;

	// ü��
	float hp_current;
	float hp_max;

	// ���ݷ�
	float attack;

	// �̵��ӵ�
	float speed_move;

public:
	Missile();
	~Missile();

	static Missile* create(const std::string &filename);

	void setImageInfo(const std::string *filename, const int fileNum);

	// set ability
	void setHP(float hp);
	void setAttack(float atk);
	void setSpeed(float spd);
	float getHP();
	// float getAttack();
	float getSpeed();

	virtual void getDamage(int enemyAttack);
	void deathAnimation();
	void destroy();
};

