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
const int GameData::enemyAttackRange = 50;

const float GameData::enemyAttackSpeed = 1.0;

const float GameData::enemyMoveSpeed = 10.0;

const int GameData::enemyMutateRate[21] = {
	0, 5, 10, 15, 20, 26, 32, 39, 47, 56, 67, 80, 81, 82, 83, 84, 85, 86, 87, 88
};

const int GameData::enemyLevelUpRate[21] = {
	0, 0, 0, 0, 0
};