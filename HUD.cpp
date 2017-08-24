#include "HUD.h"

HUD *HUD::create()
{
	HUD *pRet = new HUD();
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
	// 게이지 필요할때 새로고침
}

void HUD::renewTimer()
{
	// 타이머 변경
	// 타이머 상태 관리 등
}

void HUD::renewMoney()
{
	// 돈이 프레임*5쯤 올라가게 하는 schedule을 돌림
	// schedule이 지 알아서 끝나면 꺼야함
}