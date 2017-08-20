#pragma once
#include "Mutate.h"
#include <string>

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

	// ���� �ɷ�ġ�� �̹���
	extern const float enemyMutateStatus[5][6][5];
	extern const std::string enemyMutateImage[5][6];

	// ���� ���� �̹���
	extern const std::string enemyDeathAnimation[12];
	extern const std::string eMissileBoomAnimation[6];
	extern const std::string pMissileBoomAnimation[4];
}