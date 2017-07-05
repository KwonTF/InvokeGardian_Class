#include "PopUp.h"

const int PopUp::zOrder = 100;

PopUp::PopUp()
{
	parentLayer = nullptr;

	pCallback = nullptr;
}

PopUp::~PopUp()
{
	parentLayer = nullptr;

	pCallback = nullptr;
}

PopUp *PopUp::create(Sprite  *BgBoard, Sprite  *BgImg)
{
	PopUp *pRet = new PopUp();
	if (pRet && pRet->init())
	{
		//pRet->setBgBoard(BgBoard);
		//pRet->setBgImg(BgImg);
		//pRet->setTextInit(); //출력할 문자 UI초기화

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

// 클래스에서 부를 함수 설정
void PopUp::setCallbackFunc(const popupCallback &callback)
{
	pCallback = callback;
}

// 팝업 태그 불러오기(버튼 태그 기준으로 if문 짤 것)
int PopUp::getBtnTag()
{
	return btnTag;
}

// 팝업레이어를 불러오고 부모레이어 정지
void PopUp::call(Layer *pLayer)
{
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//popupLayer->setPosition(Global::screenSizeX / 2, Global::screenSizeY / 2);
	// Need define popupLayer Zorder variable
	parentLayer->addChild(this, PopUp::zOrder);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(parentLayer, true);
}

// 팝업 닫기
void PopUp::close()
{
	//setTouchEnabled(false);

	if (parentLayer) 
	{
		//parentLayer->setTouchEnabled(true);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(parentLayer, true);
	}

	removeAllChildren();
	removeFromParent();
}

// 팝업 버튼 콜백함수 설정
void PopUp::onBtnCallbackFunc(Ref *pSender, ui::Widget::TouchEventType touchType)
{
	/*
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		btnTag = ((Button*)pSender)->getTag();
		onCallbackFunc();
	}
	*/
}

// 함수 부르기
void PopUp::onCallbackFunc()
{
	if (pCallback)
		pCallback(parentLayer);
}