#include "HUD.h"

HUD *HUD::create()
{
	HUD *pRet = new HUD();
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

void HUD::upgradeSetting()
{

}

void HUD::gageBarSetting()
{

}

void HUD::timerViewerSetting()
{

}

void HUD::renewGage()
{
	// ������ �ʿ��Ҷ� ���ΰ�ħ
}

void HUD::renewTimer()
{
	// Ÿ�̸� ����
	// Ÿ�̸� ���� ���� ��
}

void HUD::renewMoney()
{
	// ���� ������*5�� �ö󰡰� �ϴ� schedule�� ����
	// schedule�� �� �˾Ƽ� ������ ������
}