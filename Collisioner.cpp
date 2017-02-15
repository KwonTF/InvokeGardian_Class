#include "Collisioner.h"

Collisioner* Collisioner::create(const std::string &filename)
{
	Collisioner *object = new (std::nothrow) Collisioner();

	if (object && object->initWithFile(filename))
	{
		object->autorelease();
		return object;
	}

	CC_SAFE_DELETE(object);
	return nullptr;
}

int Collisioner::getAttack()
{
	return attack;
}

Condition Collisioner::getCondition()
{
	return deliveryCondition;
}

// function for collision act
// damage - 상대와 부딪히면 얻게 될 데미지
// condition - 상대와 부딪히면 얻게 될 상태이상
void Collisioner::collisioned(int damage, Condition condition)
{

}