#include "PopUp.h"

const int PopUp::zOrder = 100;
const int PopUp::zBoardPos = -10;
const int PopUp::zImgPos = -1;
const int PopUp::zBtnPos = 1;

PopUp::PopUp()
{
	parentLayer = nullptr;

	pCallback = nullptr;

	btnTag = 1;
	isPause = true;
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

// 백그라운드 보드 설정 (최적화 작업중)
void PopUp::setBgBoard(Sprite *BgBoard)
{
	if (BgBoard)
		return;
	else
	{
		bgBoard = BgBoard;
	}

	Size size = Director::getInstance()->getWinSize();
	BgBoard->setPosition(size.width / 2, size.height / 2);
	addChild(BgBoard, zBoardPos);
}

// 백그라운드 이미지 설정 (최적화 작업중)
void PopUp::setBgImg(Sprite *BgImg)
{
	if (BgImg)
	{
#if COCOS2D_DEBUG > 0
		char msg[256] = { 0 };
		sprintf(msg, "Already BackgroundImage");
		CCASSERT(bgImg == nullptr, msg);
#endif
		return;
	}

	bgImg = BgImg;
	if (!bgImg)return;

	Size size = Director::getInstance()->getWinSize();
	bgImg->setPosition(size.width / 2, size.height / 2);
	addChild(bgImg, zImgPos);
}

// 클래스에서 부를 함수 설정
void PopUp::setCallbackFunc(const popupCallback &callback)
{
	pCallback = callback;
}

void PopUp::setPauseParentLayer(const bool pause)
{

}

void PopUp::addButton
(const std::string& normalTexture, const std::string& selectedTexture,
const std::string& disabledTexture, ui::Widget::TextureResType texType,
const Vec2 &pos, const std::string& text, const int nTag)
{
	//팝업창에 버튼을 생성한다.
	cocos2d::ui::Button *pBtn = cocos2d::ui::Button::create();
	pBtn->setTouchEnabled(true);
	pBtn->loadTextures(normalTexture, selectedTexture, disabledTexture, texType);
	pBtn->setTitleText(text);
	if (bgImg)
	{
		Vec2 btnPos(pos.x + bgImg->getPositionX(), pos.y + bgImg->getPositionY());
		pBtn->setPosition(btnPos);
	}
	else
	{
		pBtn->setPosition(pos);
	}

	pBtn->setTag(nTag);	// 태그 설정
	pBtn->addTouchEventListener(CC_CALLBACK_2(PopUp::onBtnCallbackFunc, this)); //버튼이 클릭시 콜백함수 설정

	addChild(pBtn, (int)zOrder + zBtnPos);
}

// 팝업 태그 불러오기(버튼 태그 기준으로 if문 짤 것)
const int PopUp::getBtnTag()
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