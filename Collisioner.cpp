#include "Collisioner.h"

Collisioner::~Collisioner()
{
}

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
	return 0;
}

Condition* Collisioner::getCondition()
{
	return deliveryCondition;
}

void Collisioner::collisioned(int damage, Condition *c)
{

}