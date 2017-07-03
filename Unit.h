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
	int hpRegen;

	// �̵��ӵ�
	float moveSpeed;

	// shadow effect
	Vec2 previousPosition[4];

	// sub Sprite
	Sprite *hpGage;
	Sprite *shadow[4];
public:
	Unit();
	~Unit();

	static Unit* create(const std::string &filename);

	virtual void collisioned(int damage, std::vector<Condition*> &c) override;

	void setImageInfo(const std::string *filename, const int fileNum);

	// set ability
	void setHP(int hp);
	void setHPRegen(int regen);
	void setAttack(int atk);
	void setSpeed(float spd);

	// get ability
	int getHP();
	float getSpeed();

	// add sub sprite
	void setHpGage(const std::string &filename);
	void projectImage(const std::string &filename);

	// remove object
	void deathAnimation();
	virtual void destroy();

	//��Ʈ�� ���� �Լ�
	void takenDamage(int taken);

	// schedule function
	void regeneration(float dt);
	void shadowEffect(float dt);
};

