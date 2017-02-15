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
// damage - ���� �ε����� ��� �� ������
// condition - ���� �ε����� ��� �� �����̻�
void Collisioner::collisioned(int damage, Condition condition)
{

}