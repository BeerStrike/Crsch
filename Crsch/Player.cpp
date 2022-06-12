#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>
Player::Player(Map* mp):Person(mp, mp->getPlayerX() * 100 + 50, mp->getPlayerY() * 100 + 50)
{
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

double* Player::raycast(int num)
{
	double* heights=new double[2*num];
	double step = (M_PI / 3) / num;
	int n = 0;
	double mgs =300;
	for (double i = angle+M_PI / 6; i > angle-M_PI / 6; i -= step) {
		for (int j = 0; j < mgs; j++) {
			int xm = (x + j * cos(i)) / 100;
			int ym = (y +  - j * sin(i)) / 100;
			if (map->at(xm, ym) == 1) {
				double nw = (mgs - j) / mgs;
				heights[n]=nw;
				break;
			}
		}
		n++;
	}
	return heights;
}
double Player::getAngle()
{
	return angle;
}
