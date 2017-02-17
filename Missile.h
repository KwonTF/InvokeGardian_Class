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

	// �̵��ӵ�
	float speed;

	int range;				// ��Ÿ� ����
	int penetrationCount;	// ���� ������ ���� ��
	int divideCount;		// �п� ��

public:
	Missile() {};
	~Missile() {};

	static Missile* create(const std::string &filename);

	void collisioned(int damage, Condition *c);

	// set ability
	void setAttack(int atk);

	void setSpeed(int s);
	void setRange(int movelimit);
	void setPenetCount(int count);
	void setDivideCount(int count);

	void setMissileTeam(int team);

	float getSpeed();

	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};

