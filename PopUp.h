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

	int btnTag;

	popupCallback pCallback;
public:
	PopUp();
	virtual ~PopUp();

	static PopUp* create(Sprite  *BgBoard, Sprite  *BgImg);

	void setCallbackFunc(const popupCallback &callback);
	void setPauseParentLayer(const bool);

	int getBtnTag();

	void onBtnCallbackFunc(Ref *pSender, cocos2d::ui::Widget::TouchEventType touchType);

	void call(Layer *pLayer);
	void close();
protected:
	virtual void onCallbackFunc();
};