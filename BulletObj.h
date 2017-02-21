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
	void pushEffects(Condition* input);
	static BulletObj* createAndInit(float rotation);
	int getArraySize();
	Condition* sendCondition(int i);
private:
	float x, y;
	std::vector<Condition*> EffectArray;
};
#endif // BULLET_OBJ_H


