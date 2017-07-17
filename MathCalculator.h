#pragma once
#include "math\Vec2.h"
#include <math.h>

namespace MathCalculator {
	inline cocos2d::Vec2 calculateUnitVec2(const cocos2d::Vec2 &current, const cocos2d::Vec2 &point)
	{
		return cocos2d::Vec2(point.x - current.x, point.y - current.y).getNormalized();
	}

	inline float calculateAngle(const cocos2d::Vec2 &current, const cocos2d::Vec2 &point)
	{
		return calculateUnitVec2(current, point).getAngle();
	}

	inline double radian() { return 180 / M_PI; }
};