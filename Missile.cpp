#include "Missile.h"

Missile::Missile()
	: speed(400.0), range(200),
	penetrationCount(1), divideCount(0),
	isExplode(false), explodeDamage(30),
	removeTime(0.1f){}



Missile* Missile::create(const std::string &filename)
{
	Missile *missile = new (std::nothrow) Missile();

	if (missile && missile->initWithFile(filename))
	{
		missile->autorelease();
		return missile;
	}

	CC_SAFE_DELETE(missile);
	return nullptr;
}

/*
set unit image infomation
filename : file root of unit's image
fileNum : number of unit's image
*/
void Missile::setDeathAnimFile(const std::string * const filename, const int fileNum)
{
	image = new std::string[fileNum];
	for (int i = 0; i < fileNum; i++)
	{
		image[i] = filename[i];
	}
	imageNum = fileNum;
}

void Missile::setDeathAnimFile2
(const std::string filename, const int row, const int colm, const int width, const int height, const float delay)
{
	deathAnimTexture = filename;
	deathAnimRow = row;
	deathAnimColm = colm;
	deathAnimWidth = width;
	deathAnimHeight = height;
	deathAnimDelay = delay;
}

void Missile::make()
{
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2, material);

	// 몸체 설정
	this->setPhysicsBody(body);
}

// if Missile collisioned
void Missile::collisioned(int damage, std::vector<Condition*> &c)
{
	penetrationCount--;

	if(isExplode)
		makeExplosion();

	if (penetrationCount <= 0)
		destroy();
}

/*
remove Missile without death animation
warning : need PhysicsBody
*/
void Missile::removeMissile(float f)
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	removeFromParent();
}

//미사일 요소 적용 함수
void Missile::castEffect()
{
	std::vector<Condition*>::iterator iter;
	for (iter = conditionArray.begin(); iter != conditionArray.end(); iter++) 
	{
		attack += (*iter)->elementDamage;
		switch ((*iter)->getCode())
		{
		case EffectCode::PowerUp:
			range += (*iter)->castEffect(range);
			penetrationCount += (*iter)->castSideEffect(penetrationCount);
			break;
		case EffectCode::Division:
			break;
		case EffectCode::Explode:
			isExplode = true;
			explodeDamage = 30;
			explodeRadius = (*iter)->castEffect(3);
			break;
		case EffectCode::Mine:
			getPhysicsBody()->setVelocity(Vec2(0,0));
			range += (*iter)->castEffect(range)*speed;
			break;
		default:
			break;
		}
	}
	scheduleOnce(schedule_selector(Missile::removeMissile), (float)range / speed);
}

void Missile::makeExplosion()
{
	Explosion* explosion = Explosion::create("UI/SkillBox.PNG");

	// 내부 값 설정
	explosion->setAttack(explodeDamage);

	// 몸체 설정
	auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);

	auto body = PhysicsBody::createCircle(explodeRadius, material);

	explosion->setPhysicsBody(body);
	explosion->setPhysicsBitmask(Collisioner::bitmaskBulletOne, ~(Collisioner::bitmaskBulletAll + Collisioner::bitmaskPlayerAll), Collisioner::bitmaskZero);
	explosion->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	explosion->destroy();
	explosion->setPosition(this->getPosition());

	if (getParent() != nullptr)
	{
		getParent()->addChild(explosion);
	}
}

// make Missile's death animation
void Missile::deathAnimation()
{
	// 단편 파일 재생 방식
	Vector<SpriteFrame*> animFrames(imageNum - 1);
	
	for (int i = 1; i < imageNum; i++)
	{
		auto frame = SpriteFrame::create(image[i], Rect(0, 0, 32, 32));
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	auto animate = Animate::create(animation);
	runAction(animate);
}

// destory unit from game
void Missile::destroy()
{
	// delete PhysicsBody
	getPhysicsBody()->removeFromWorld();

	auto callback1 = CallFunc::create(CC_CALLBACK_0(Missile::deathAnimation, this));
	auto callback2 = CallFunc::create(CC_CALLBACK_0(Missile::removeFromParent, this));
	auto sequence = Sequence::create(callback1, DelayTime::create(0.1f * (imageNum - 1)), callback2, nullptr);
	//deathAnimDelay * (deathAnimRow * deathAnimColm - 1)
	runAction(sequence);
}