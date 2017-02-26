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

void Player::gotoPoint(float x, float y, float angle)
{
	movePointX = sinf((angle-90)*(-1));
	movePointY = cosf((angle - 90)*(-1));
	unscheduleAllSelectors();

	schedule(schedule_selector(Player::moveBySpeed));
}

void Player::moveBySpeed(float input)
{
	this->setPositionX(this->getPositionX() + (movePointX * 100 * input));
	this->setPositionY(this->getPositionY() + (movePointY * 100 * input));
}
