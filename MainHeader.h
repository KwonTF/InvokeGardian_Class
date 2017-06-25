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

// 고정값
const unsigned int ROUNDTIME = 90;
const unsigned int SETUPTIME = 45;
const unsigned int _MPSIZERATE = 52;

// 전역 변수(옵션, 디버깅용)
