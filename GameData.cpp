#include "GameData.h"
/*
GameData���� ������ ������ ���⼭ �ʱ�ȭ�� ��
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