#pragma once
#include "Collisioner.h"

/*
타워 내 터렛 정보 클래스
create by ZeroFe
*/
class Turret : public Collisioner
{
private:
	int id;				// 터렛 ID

	int attack;			// 공격력
	int attackSpeed;	// 공격 속도
	int weight;			// 터렛 무게

	int rad;
public:
	Turret();
	~Turret() {};

	void setID(int _id);
	void setTurretAbillity(int atk, int atkSpeed, int weight);

	int getAttack();
	int getAttackSpeed();
	int getWeight();

	bool anyRay(PhysicsWorld &world, const PhysicsRayCastInfo &info, void *data);

	// schedule function
	void checkEnemy(float dt);
	void attackCharge(float dt);

	virtual void collisioned(int damage, std::vector<Condition*> &c);
private:
	DrawNode* _node;
};