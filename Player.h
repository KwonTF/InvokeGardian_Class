#pragma once
/*******************************
Invoke Gardian Player 파일(cpp, h)
----------------------------------
작성자: 권태형
********************************/
#ifndef PLAYER
#define PLAYER
#include "cocos2d.h"
#include "MainHeader.h"

USING_NS_CC;
class Player : public Sprite
{
public:
	Player();
	~Player();
	static Player* createAndInit();
	void gotoPoint(Vec2 point, float angle);
	void moveBySpeed(float input);
private:
	float movePointX, movePointY;
	Vec2 DestPoint;
};
#endif // BULLET_OBJ_H