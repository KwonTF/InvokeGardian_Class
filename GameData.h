#pragma once
#include "Mutate.h"
#include <string>

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

	// 변이 능력치와 이미지
	extern const float enemyMutateStatus[5][6][5];
	extern const std::string enemyMutateImage[5][6];

	// 폭발 관련 이미지
	extern const std::string enemyDeathAnimation[12];
	extern const std::string eMissileBoomAnimation[6];
	extern const std::string pMissileBoomAnimation[4];
}