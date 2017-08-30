#include "Unit.h"

Unit::Unit()
{
	hpCurrent = 0;
	hpMax = 0;
	hpRegen = 0;

	moveSpeed = 0;

	hpGage = nullptr;

	for (int i = 0; i < 4; i++)
	{
		shadow[i] = nullptr;
	}
}

Unit::~Unit()
{

}

/*
set unit image infomation
filename : file root of unit's image
fileNum : number of unit's image
*/
void Unit::setDeathAnimFile(const std::string * const filename, const int fileNum)
{
	image = new std::string[fileNum];
	for (int i = 0; i < fileNum; i++)
	{
		image[i] = filename[i];
	}
	imageNum = fileNum;
}

Unit* Unit::create(const std::string &filename)
{
	Unit *unit = new (std::nothrow) Unit();

	if (unit && unit->initWithFile(filename))
	{
		unit->autorelease();
		return unit;
	}

	CC_SAFE_DELETE(unit);
	return nullptr;
}

void Unit::make()
{
	Collisioner::make();
	this->getPhysicsBody()->setDynamic(false);
}

void Unit::collisioned(int damage, std::vector<Condition*> &c)
{
	conditionArray = c;

	// 폭발시 중복삭제 예방
	if (hpCurrent < 0)
		return;

	takenDamage(damage);

	if (hpCurrent > hpMax)
		hpCurrent = hpMax;

	if (hpCurrent <= 0)
 		destroy();

	if (hpGage != nullptr)
	{
		if (hpCurrent > 0)
 			hpGage->setScaleX((float)hpCurrent / hpMax);
		else
			hpGage->setOpacity(0);
	}

	log("Unit collisioned : hp - %d, damage - %d", hpCurrent, damage);
}

void Unit::setHpGage(const std::string &filename)
{
	hpGage = Sprite::create(filename);
	hpGage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	hpGage->setPosition(getContentSize().width / 2, 0);
	addChild(hpGage);
}

void Unit::projectImage(const std::string &filename)
{
	for (int i = 0; i < 4; i++)
	{
		// shadow들 선언
		shadow[i] = Sprite::create(filename);
		shadow[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		shadow[i]->setPosition(Vec2::ZERO);
		addChild(shadow[i], -1);
		shadow[i]->setOpacity(204 - (51 * i));

		// 이전 위치 찾기
		previousPosition[i] = getPosition();
	}

	schedule(schedule_selector(Unit::shadowEffect), 0.25f);
}

// make Unit's death Animation
void Unit::deathAnimation()
{
	Vector<SpriteFrame*> animFrames(imageNum - 1);

	for (int i = 1; i < imageNum; i++)
	{
		auto frame = SpriteFrame::create(image[i], Rect(0, 0, 50, 50)); //we assume that the sprites' dimentions are 40*40 rectangles.
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	runAction(animate);
}

// destory unit from game
void Unit::destroy()
  {
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	auto callback1 = CallFunc::create(CC_CALLBACK_0(Unit::deathAnimation, this));
	auto callback2 = CallFunc::create(CC_CALLBACK_0(Unit::removeFromParent, this));
	auto sequence = Sequence::create(callback1, DelayTime::create((float)(imageNum-1)/10), callback2, nullptr);

	runAction(sequence);
}

void Unit::takenDamage(int taken)
{
	hpCurrent -= taken;
	//if(hpCurrent <=0)
		//destroy();
}

void Unit::regeneration(float dt)
{
	if (hpMax <= hpCurrent + hpRegen)
	{
		hpCurrent = hpMax;
	}
	else
	{
		hpCurrent += hpRegen;
	}
}

void Unit::shadowEffect(float dt)
{
	shadow[3]->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2) + previousPosition[3] - getPosition());
	previousPosition[3] = previousPosition[2];
	shadow[2]->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2) + previousPosition[2] - getPosition());
	previousPosition[2] = previousPosition[1];
	shadow[1]->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2) + previousPosition[1] - getPosition());
	previousPosition[1] = previousPosition[0];
	shadow[0]->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2) + previousPosition[0] - getPosition());
	previousPosition[0] = getPosition();
}