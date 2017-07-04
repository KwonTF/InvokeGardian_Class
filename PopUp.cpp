#include "PopUp.h"

const int PopUp::zOrder = 100;

PopUp::PopUp()
{
	parentLayer = nullptr;
}

PopUp::~PopUp()
{
	parentLayer = nullptr;
}

PopUp *PopUp::create(Sprite  *BgBoard, Sprite  *BgImg)
{
	PopUp *pRet = new PopUp();
	if (pRet && pRet->init())
	{
		pRet->setBgBoard(BgBoard);
		pRet->setBgImg(BgImg);
		//pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void PopUp::setBgBoard(Sprite *BgBoard)
{

}

void PopUp::setBgImg(Sprite *BgImg)
{

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
void PopUp::call()
{
	/*
	popupLayer->setAnchorPoint(Vec2(0.5, 0.5));
	popupLayer->setPosition(Global::screenSizeX / 2, Global::screenSizeY / 2);
	// Need define popupLayer Zorder variable
	parentLayer->addChild(popupLayer, POPUP_ZORDER);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(parentLayer, true);
	*/
}

// �˾� �ݱ�
void PopUp::close()
{
	/*
	parentLayer->removeChild(popupLayer, true);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(parentLayer, true);
	*/
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