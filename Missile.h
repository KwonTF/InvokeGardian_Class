#pragma once
#include "cocos2d.h"
#include "Collisioner.h"
#include "Explosion.h"

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

	int penetrationCount;	// ���� Ƚ��
	int range;				// ��Ÿ� ����
	int divideCount;		// �п� ��

	bool isExplode;			// ���� ����
	int explodeDamage;		// ���� ������ ����

	float removeTime;		// �Ѿ� �����ִ� �ð�
public:
	Missile();
	~Missile() {};

	static Missile* create(const std::string &filename);

	virtual void collisioned(int damage, std::vector<Condition*> &c);

	// set ability
	void setAttack(int atk);
	void setSpeed(int s);
	void setRange(int movelimit);
	void setPenetCount(int count);
	void setDivideCount(int count);

	void setMissileTeam(int team);
	void setRemoveTime(float time);

	float getSpeed();
	float getRange();

	//�̻��� ��� ���� �Լ�
	void castEffect();
	void makeExplosion();
	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};

