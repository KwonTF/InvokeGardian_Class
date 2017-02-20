#include "Tower.h"

Tower* Tower::create(const std::string &filename)
{
	Tower *tower = new (std::nothrow) Tower();

	if (tower && tower->initWithFile(filename))
	{
		tower->autorelease();
		return tower;
	}

	CC_SAFE_DELETE(tower);
	return nullptr;
}

// �ӽ÷� �⺻��(1�ܰ�) ������
// ���� ���� �ٶ�
void Tower::setTowerBase()
{
	hpCurrent = 500;
	hpMax = 500;
	hpRegen = 0;
	maxWeight = 30;
	turretArea = 1;
}