#pragma once
#include "PopUp.h"

/*
���̾ �ټ��� �˾�
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