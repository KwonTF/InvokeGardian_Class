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

// 임시로 기본값(1단계) 설정함
// 추후 수정 바람
void Tower::setTowerBase()
{
	hpCurrent = 500;
	hpMax = 500;
	hpRegen = 0;
	maxWeight = 30;
	turretArea = 1;
}