#pragma once
#include "PopUp.h"

/*
���̾ �ټ��� �˾�
creater : ZeroFe
*/
class MultiLayerPopUp : public PopUp
{
private:

public:
	MultiLayerPopUp();
	~MultiLayerPopUp();

	static MultiLayerPopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void addLayer(Layer *cLayer);
};