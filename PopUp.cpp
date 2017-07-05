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
		//pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

// Ŭ�������� �θ� �Լ� ����
void PopUp::setCallbackFunc(const popupCallback &callback)
{
	pCallback = callback;
}

// �˾� �±� �ҷ�����(��ư �±� �������� if�� © ��)
int PopUp::getBtnTag()
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