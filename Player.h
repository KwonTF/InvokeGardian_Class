#pragma once
/*******************************
Invoke Gardian Player ����(cpp, h)
----------------------------------
�ۼ���: ������
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