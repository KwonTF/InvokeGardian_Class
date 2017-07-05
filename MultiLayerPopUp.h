#pragma once
#include "PopUp.h"

/*
레이어가 다수인 팝업
creater : ZeroFe
*/
class MultiLayerPopUp : public cocos2d::Layer
{
private:

public:
	MultiLayerPopUp();
	~MultiLayerPopUp();

	static MultiLayerPopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void addLayer();
};