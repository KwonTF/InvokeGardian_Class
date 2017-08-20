#include "GameData.h"
/*
GameData에서 선언한 변수들 여기서 초기화할 것
*/

const int GameData::roundEnemyHP[21] = {
	10, 50, 60
};
const int GameData::roundEnemyAttack[21] = {
	2, 10, 12
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
	0, 5, 10, 15, 20, 26, 32, 39, 47, 56, 67, 80, 81, 82, 83, 84, 85, 86, 87, 88
};

const int GameData::enemyLevelUpRate[21] = {
	0, 0, 0, 0, 0
};

// 변이 능력치
// 작성 순서 - normal / range / mass / divide / golem / faster 순
// 능력치 순서 - 체력, 사거리, 공격력, 이동속도, 공격속도
const float GameData::enemyMutateStatus[5][6][5] = {
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 0.70, 4.00, 1.00, 1.00, 1.00 }, { 0.50, 1.00, 0.50, 1.40, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }},
	{{ 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }, { 1.00, 1.00, 1.00, 1.00, 1.00 }}
};

const std::string GameData::enemyMutateImage[5][6] = {
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" },
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" },
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" },
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" },
	{ "Unit/Normal.png", "Unit/Range.png", "Unit/Mass.png", "Unit/Divide.png", "Unit/Golem.png", "Unit/Faster.png" }
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