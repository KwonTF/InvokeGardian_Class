#pragma once
#include <vector>
#include <string>
#include <time.h>

// ��ü ���� �ڵ�
#include "Missile.h"
#include "Enemy.h"
#include "Tower.h"
#include "Player.h"
#include "BulletObj.h"
#include "GameData.h"
#include "MathCalculator.h"
#include "MultiLayerPopUp.h"

// ������
const unsigned int ROUNDTIME = 90;
const unsigned int SETUPTIME = 45;
const int _MPSIZERATE = 90;
const int secondPerFrame = 60;
const int MUTATE_MAXLEVEL = 5;
const int ROUND_MONEY = 1000;
const int popLayerBtnSizeY = 154;


// ���� ����(�ɼ�, ������)

// ����� üũ ����
const bool DEBUGMODE = true;

// ���� ���� ����
// �ɼ����� ���� �����ϰ� ����� �� ������(���߿� const ���ְ� constexpr�� �ٲ���)
const int monsterBaseAmount = 16;		// �⺻ ������
const int monsterBaseBonus = 4;			// ���� �� �߰� ������