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

void Player::gotoPoint(float x, float y)
{
	this->runAction(MoveTo::create(3.0, Point(x, y)));
}

void Player::moveBySpeed(float input)
{
	this->setPositionX(this->getPositionX() + (movePointX * 100 * input));
	this->setPositionY(this->getPositionY() + (movePointY * 100 * input));
}
