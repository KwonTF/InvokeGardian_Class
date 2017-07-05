#pragma once
#include "PopUp.h"

/*
base class of pop up
creater : ZeroFe
*/
class SingleLayerPopUp : public cocos2d::Layer
{
private:
	Sprite *bgBoard;
	Sprite *bgImg;
public:
	SingleLayerPopUp();
	~SingleLayerPopUp();

	static SingleLayerPopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void setBgBoard(Sprite *BgBoard);
	void setBgImg(Sprite *BgImg);

	void addButton(const std::string& normalTexture, const std::string& selectedTexture,
		const std::string& disabledTexture, ui::Widget::TextureResType texType,
		const Vec2 &pos, const std::string& text, const int nTag);
};