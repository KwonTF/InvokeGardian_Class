#pragma once
#ifndef BULLET_OBJ_H
#define BULLET_OBJ_H
#include "cocos2d.h"
#include "MainHeader.h"
USING_NS_CC;

class BulletObj : public Sprite
{
public:
	BulletObj();
	~BulletObj();
	void update(float input);
	static BulletObj* createAndInit(float rotation);
private:
	float x, y;
};
#endif // BULLET_OBJ_H


