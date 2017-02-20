#pragma once
#include "cocos2d.h"
#include "Unit.h"

class Tower : public Unit
{
// ���� ���
private:
	// ������ ��� �߰� �κ�
	int maxWeight;
	int turretArea;

	// ��ž �κ�
	
	// ��ȣ�� �κ�

public:
	Tower() {};
	~Tower() {};

	static Tower* create(const std::string &filename);

	void setTowerBase();
	
};

class Turret
{
friend class Tower;

private:
	int id;
	std::string name;

	int attack;
	int attackSpeed;

	int weight;

	// �߻��ϴ� �̻��� ����
};