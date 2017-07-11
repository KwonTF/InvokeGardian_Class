#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

typedef std::function<void(Ref*)> popupCallback;

/*
base class of pop up
creater : ZeroFe
*/
class PopUp : public cocos2d::Layer
{
protected:
	static const int zOrder;

	Layer *parentLayer;

	Sprite *bgBoard;
	Sprite *bgImg;

	int btnTag;

	popupCallback pCallback;
public:
	PopUp();
	virtual ~PopUp();

	static PopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void setBgBoard(Sprite *BgBoard);
	void setBgImg(Sprite *BgImg);
	void setCallbackFunc(const popupCallback &callback);
	void setPauseParentLayer(const bool);

	void addButton(const std::string& normalTexture, const std::string& selectedTexture,
		const std::string& disabledTexture, ui::Widget::TextureResType texType,
		const Vec2 &pos, const std::string& text, const int nTag);

	int getBtnTag();

	void onBtnCallbackFunc(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);

	void call(Layer *pLayer);
	void close();
protected:
	virtual void onCallbackFunc();
};