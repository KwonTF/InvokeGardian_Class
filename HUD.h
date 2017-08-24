#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
base class of HUD
creater : ZeroFe
*/
class HUD : public cocos2d::Layer
{
private:
	Size winSize;
public:
	Sprite* Background;
	Layer* layerMissile;
	Sprite* statusBar;

	Sprite* mpSprite;
	CCProgressTimer* mpBar;
	Label* mpState;

	Sprite* hpSprite;
	CCProgressTimer* hpBar;
	Label* hpState;

	Label* ttf1;

	// 12시 방향 시간 표기
	Label* roundViewer;
	Label* timeViewer;

	// 1시 방향 적군 수 표기
	Label* monsterPresentViewer;
	Label* monsterExistViewer;
public:
	HUD() {};
	~HUD() {};

	static HUD* create();

	inline void setSize(const Size _winSize) { winSize = _winSize; }
	inline const Size getSize() { return winSize; }

	void upgradeSetting();
	void gageBarSetting();
	void timerViewerSetting();

	void renewGage();
	void renewTimer();
	void renewMoney();
};