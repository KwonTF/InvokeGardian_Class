#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Player * Player::createAndInit()
{
	Player* player = new Player();
	player->initWithFile("Unit/Player.png");
	player->autorelease();
	player->setAnchorPoint(Vec2(0.5, 0.5));
	return player;
}

void Player::gotoPoint(Vec2 point, float angle)
{
	unscheduleAllSelectors();
	DestPoint = point;
	movePointX = sinf(CC_DEGREES_TO_RADIANS(90 - angle));
	movePointY = cosf(CC_DEGREES_TO_RADIANS(90- angle));
	schedule(schedule_selector(Player::moveBySpeed));
}

void Player::moveBySpeed(float input)
{
	this->setPositionX(this->getPositionX() + (movePointX * 100 * input));
	this->setPositionY(this->getPositionY() + (movePointY * 100 * input));
}
