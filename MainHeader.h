#pragma once
#include <vector>
#include <string>
#include <time.h>

// 자체 제작 코드
#include "Missile.h"
#include "Enemy.h"
#include "Tower.h"
#include "Player.h"
#include "BulletObj.h"
#include "GameData.h"
#include "MathCalculator.h"
#include "MultiLayerPopUp.h"

// 고정값
const unsigned int ROUNDTIME = 90;
const unsigned int SETUPTIME = 45;
const int _MPSIZERATE = 90;
const int secondPerFrame = 60;
const int MUTATE_MAXLEVEL = 5;
const int ROUND_MONEY = 1000;
const int popLayerBtnSizeY = 154;


// 전역 변수(옵션, 디버깅용)

// 디버그 체크 변수
const bool DEBUGMODE = true;

// 몬스터 생성 관련
// 옵션으로 조절 가능하게 만들어 볼 생각임(나중에 const 없애고 constexpr로 바꾸자)
const int monsterBaseAmount = 16;		// 기본 생성량
const int monsterBaseBonus = 4;			// 라운드 별 추가 생성량