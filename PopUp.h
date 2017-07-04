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
private:
	static const int zOrder;
private:
	Layer *parentLayer;

	Sprite *bgBoard;
	Sprite *bgImg;

	int btnTag;

	popupCallback pCallback;
public:
	PopUp();
	~PopUp();

	static PopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void setBgBoard(Sprite *BgBoard);
	void setBgImg(Sprite *BgImg);
	void addButton(const char* normalTexture, const char* selectedTexture, 
		const char* disabledTexture, ui::Widget::TextureResType texType, 
		const Point &pos, const std::string& text, const int nTag);
	void setButton(const std::string &name, const int tag);
	void setCallbackFunc(const popupCallback &callback);

	int getBtnTag();

	void onBtnCallbackFunc(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);

	void call();
	void close();
private:
	virtual void onCallbackFunc();
};