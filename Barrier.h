#pragma once

/*
Ÿ�� ��(ü�� ����) Ŭ����
create by ZeroFe
*/
class Barrier {
private:
	int id;

	int hp;
	int recovery;

	int maxWeight;
	int turretArea;
public:
	Barrier();
	~Barrier() {};

	void setID(int _id);
	void setBarrierAbillity(int _hp, int _recovery, int mWeight, int tArea);

	int getHP();
	int getRecovery();
	int getMaxWeight();
	int getTurretArea();
};