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

	// ���ݷ�
	float attack;

	// �̵��ӵ�
	float speed;

	int range;				// ��Ÿ� ����
	int penetrationCount;	// ���� ������ ���� ��
	int divideCount;		// �п� ��

public:
	Missile() {};
	~Missile() {};

	static Missile* create(const std::string &filename);

	// set ability
	void setRange(int movelimit);
	void setPenetCount(int count);
	void setDivideCount(int count);

	void setMissileTeam(int team);

	int getAttack();
	float getSpeed();

	void getDamage(int enemyAttack);
	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};

