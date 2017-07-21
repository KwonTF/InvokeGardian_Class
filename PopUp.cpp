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
		//pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

// ��׶��� ���� ���� (����ȭ �۾���)
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

// ��׶��� �̹��� ���� (����ȭ �۾���)
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

// Ŭ�������� �θ� �Լ� ����
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
	//�˾�â�� ��ư�� �����Ѵ�.
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

	pBtn->setTag(nTag);	// �±� ����
	pBtn->addTouchEventListener(CC_CALLBACK_2(PopUp::onBtnCallbackFunc, this)); //��ư�� Ŭ���� �ݹ��Լ� ����

	addChild(pBtn, (int)zOrder + zBtnPos);
}

// �˾� �±� �ҷ�����(��ư �±� �������� if�� © ��)
const int PopUp::getBtnTag()
{
	return btnTag;
}

// �˾����̾ �ҷ����� �θ��̾� ����
void PopUp::call(Layer *pLayer)
{
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//popupLayer->setPosition(Global::screenSizeX / 2, Global::screenSizeY / 2);
	// Need define popupLayer Zorder variable
	parentLayer->addChild(this, PopUp::zOrder);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(parentLayer, true);
}

// �˾� �ݱ�
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

// �˾� ��ư �ݹ��Լ� ����
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

// �Լ� �θ���
void PopUp::onCallbackFunc()
{
	if (pCallback)
		pCallback(parentLayer);
}