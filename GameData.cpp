#include "GameData.h"
/*
GameData에서 선언한 변수들 여기서 초기화할 것
*/

const int GameData::roundEnemyHP[21] = {
	10, 50, 60, 73, 88, 105
};
const int GameData::roundEnemyAttack[21] = {
	2, 10, 12, 15, 18, 21
};

const int GameData::roundEnemyPoint[21] = {
	1, 5, 6
};
const int GameData::mpReduce[8]{
	2, 10, 15, 23, 35, 55, 80, 101
};
const int GameData::enemyAttackRange = 100;

const float GameData::enemyAttackSpeed = 1.0;

const float GameData::enemyMoveSpeed = 10.0;

const int GameData::enemyMutateRate[21] = {
	0, 5, 80, 80, 80, 26, 32, 39, 47, 56, 67, 80, 81, 82, 83, 84, 85, 86, 87, 88
};

const int GameData::enemyLevelUpRate[21] = {
	0, 0, 0, 0, 50, 70
};

// 변이 능력치
// 작성 순서 - normal / range / mass / divide / golem / faster 순
// 능력치 순서 - 체력, 사거리, 공격력, 이동속도, 공격속도
const float GameData::enemyMutateStatus[5][6][5] = {
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.70, 2.50, 1.00, 1.00, 1.00 }, { 0.50, 1.00, 0.50, 1.40, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.50, 1.50, 1.50, 0.50, 1.20 }, { 0.60, 1.00, 1.00, 1.50, 0.85 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.50, 3.50, 1.00, 1.00, 0.75 }, { 0.40, 1.00, 0.50, 1.50, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 2.00, 1.50, 2.00, 0.45, 1.50 }, { 0.55, 1.00, 1.00, 1.80, 0.8 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.40, 4.50, 1.20, 1.00, 0.70 }, { 0.35, 1.00, 0.60, 1.50, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 3.00, 1.50, 2.50, 0.40, 1.80 }, { 0.50, 1.00, 1.00, 2.00, 0.8 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.30, 5.50, 1.40, 1.00, 0.70 }, { 0.30, 1.00, 0.50, 1.70, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 4.00, 1.50, 3.00, 0.35, 2.00 }, { 0.45, 1.00, 1.00, 2.20, 0.75 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.20, 6.60, 1.60, 1.00, 0.60 }, { 0.25, 1.00, 0.50, 1.80, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 5.00, 1.50, 3.50, 0.30, 2.50 }, { 0.40, 1.00, 1.00, 2.50, 0.7 }}
};

const std::string GameData::enemyMutateImage[5][6] = {
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" },
	{ "Unit/Normal.png", "Unit/Range2.png", "Unit/Mass2.png", "Unit/Divide2.png", "Unit/Golem2.png", "Unit/Faster2.png" },
	{ "Unit/Normal.png", "Unit/Range3.png", "Unit/Mass3.png", "Unit/Divide3.png", "Unit/Golem3.png", "Unit/Faster3.png" },
	{ "Unit/Normal.png", "Unit/Range4.png", "Unit/Mass4.png", "Unit/Divide4.png", "Unit/Golem4.png", "Unit/Faster4.png" },
	{ "Unit/Normal.png", "Unit/Range5.png", "Unit/Mass5.png", "Unit/Divide5.png", "Unit/Golem5.png", "Unit/Faster5.png" }
};

const std::string GameData::enemyDeathAnimation[12] = {
	"Unit/Explosion/0.png",
	"Unit/Explosion/1.png",
	"Unit/Explosion/2.png",
	"Unit/Explosion/3.png",
	"Unit/Explosion/4.png",
	"Unit/Explosion/5.png",
	"Unit/Explosion/6.png",
	"Unit/Explosion/7.png",
	"Unit/Explosion/8.png",
	"Unit/Explosion/9.png",
	"Unit/Explosion/10.png",
	"Unit/Explosion/11.png"
};

const std::string GameData::eMissileBoomAnimation[6] = {
	"Missile/Enemy/Boom1.png",
	"Missile/Enemy/Boom2.png",
	"Missile/Enemy/Boom3.png",
	"Missile/Enemy/Boom4.png",
	"Missile/Enemy/Boom5.png",
	"Missile/Enemy/Boom6.png"
};

const std::string GameData::pMissileBoomAnimation[4] = {
	"Missile/Player/Boom1.png",
	"Missile/Player/Boom2.png",
	"Missile/Player/Boom3.png",
	"Missile/Player/Boom4.png"
};

const std::string GameData::missileBoomAnimation = "Unit/missileExplosion.png";