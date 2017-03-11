#pragma once
#include "Collisioner.h"

/*
Ÿ�� �� �ͷ� ���� Ŭ����
create by ZeroFe
*/
class Turret : public Collisioner
{
private:
	int id;				// �ͷ� ID

	int attack;			// ���ݷ�
	int attackSpeed;	// ���� �ӵ�
	int weight;			// �ͷ� ����

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