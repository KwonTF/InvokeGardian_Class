#pragma once
#include "Mutate.h"

/*
���� �� �ʿ��� ������ ���
*/

namespace GameData {
	// �� �κ� ����ü�� ���� �� ������ ������
	extern const int roundEnemyHP[21];
	extern const int roundEnemyAttack[21];
	extern const int roundEnemyPoint[21];

	// ���ս� ���� �Ҹ�
	extern const int mpReduce[8];

	// ���� �⺻ �ɷ�ġ(����)
	extern const int enemyAttackRange;
	extern const float enemyAttackSpeed;
	extern const float enemyMoveSpeed;

	// ���� Ȯ���� �ܰ� ����
	extern const int enemyMutateRate[21];
	extern const int enemyLevelUpRate[21];

	extern const Mutate enemyRange;
}