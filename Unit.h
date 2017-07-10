#pragma once
#include "cocos2d.h"
#include "Collisioner.h"

USING_NS_CC;

typedef std::function<void()> unitCallback;

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
	inline void setHP(const int hp) {hpCurrent = hp; hpMax = hp;}
	inline void setHPRegen(const int regen) { hpRegen = regen; }
	inline void setAttack(const int atk) { attack = atk; }
	inline void setSpeed(const float spd) { moveSpeed = spd; }

	// get ability
	inline int getHPCurrent() { return hpCurrent; }
	inline int getHPMax() { return hpMax; }
	inline int getHPRegen() { return hpRegen; }
	inline float getSpeed() { return moveSpeed; }

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

