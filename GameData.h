#pragma once
#include "Mutate.h"

/*
게임 내 필요한 값들을 기록
*/

namespace GameData {
	// 이 부분 구조체로 묶을 수 있으면 좋겠음
	extern const int roundEnemyHP[21];
	extern const int roundEnemyAttack[21];
	extern const int roundEnemyPoint[21];

	// 조합시 마나 소모량
	extern const int mpReduce[8];

	// 적군 기본 능력치(고정)
	extern const int enemyAttackRange;
	extern const float enemyAttackSpeed;
	extern const float enemyMoveSpeed;

	// 변이 확률과 단계 조정
	extern const int enemyMutateRate[21];
	extern const int enemyLevelUpRate[21];

	extern const Mutate enemyRange;
}