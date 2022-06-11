#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>
Player::Player(Map* mp)
{
	map = mp;
	x = mp->getPlayerX()*100+50;
	y = mp->getPlayerY()*100+50;
	angle = 0;
}

void Player::movefrw(double dst)
{
	double nxtx =x+ dst * cos(angle);
	double nxty = y-dst * sin(angle);
	if (map->at(static_cast<int>(nxtx/100), static_cast<int>(nxty/100)) != 1) {
		x = nxtx;
		y = nxty;
	}
	
}

void Player::moveBack(double dst)
{
	movefrw(-dst);
}

void Player::rotateLeft(double rte)
{
	angle =angle+rte;
}

void Player::rotateRight(double rte)
{
	angle = angle - rte;
}

int Player::getX()
{
	return  static_cast<int>(x);
}

int Player::getY()
{
	return static_cast<int>(y);
}

double Player::getAngle()
{
	return angle;
}
