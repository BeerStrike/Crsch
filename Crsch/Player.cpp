#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>
Player::Player(Map* mp):Person(mp, mp->getPlayerX() * 100 + 50, mp->getPlayerY() * 100 + 50,100),ammo(30)
{
	angle = 0;
}

bool Player::movefrw(double dst)
{
	double nxtx =x+ dst * cos(angle);
	double nxty = y-dst * sin(angle);
	int at = map->at(static_cast<int>(nxtx / 100), static_cast<int>(nxty / 100));
	if (at == 0) {
		x = nxtx;
		y = nxty;
	}
	else if (at == 11) {
		ammo += 10;
		map->setCell(static_cast<int>(nxtx / 100), static_cast<int>(nxty / 100), 0);
	}
	else if (at == 12) {
		hp += 30;
		map->setCell(static_cast<int>(nxtx / 100), static_cast<int>(nxty / 100), 0);
	}
	else if (at == 5)
		return true;
	return false; 
	
}

bool Player::moveBack(double dst)
{
	return movefrw(-dst);
}

void Player::rotateLeft(double rte)
{
	angle =(angle+rte>2*M_PI)? angle + rte-2*M_PI: angle + rte;
}

void Player::rotateRight(double rte)
{
	angle = (angle - rte< 0) ? angle - rte + 2 * M_PI : angle - rte;
}

bool Player::shot(std::vector<Enemy*>& enm)
{
	if (ammo) {
		for (int i = 0; i < enm.size(); i++) {
			double xl = enm[i]->getX() - x;
			double yl = enm[i]->getY() - y;
			double l = sqrt(pow(xl, 2) + pow(yl, 2));
			double ang = abs((yl <= 0 ? acos(xl / l) : 2 * M_PI - acos(xl / l)) - angle);
			if (l < 400 && ang < M_PI / 20) {
				if (enm[i]->getDamage(34))
					enm.erase(enm.begin() + i);
			}
		}
		ammo--;
		return true;
	}
	return false;
}

void Player::raycast(double* heights,int num, std::vector<Enemy*>&enm)
{
	double step = (M_PI / 3) / num;
	int n = 0;
	double mgs =600;
	for (double i = angle+M_PI / 6; i > angle-M_PI / 6; i -= step) {
		for (int j = 0; j < mgs; j+=10) {
			int xm = static_cast<int>((x + j * cos(i)) / 100);
			int ym = static_cast<int>((y +  - j * sin(i)) / 100);
			if (map->at(xm, ym) == 3) {
				map->setCell(xm, ym, 0);
				enm.push_back(new Enemy(map, this, xm , ym));
			}
			int d = map->at(xm, ym);
			if (d == 1|| (d>=6&& d<=9)) {
				while (map->at(xm, ym) == 1 || (map->at(xm, ym) >= 6 && map->at(xm, ym) <= 9)) {
					xm = static_cast<int>((x + j * cos(i)) / 100);
					ym = static_cast<int>((y + -j * sin(i)) / 100);
					j--;
				}
				j++;
				double nw = pow((mgs - j) / mgs,2);
				heights[n] = nw*cos(i-angle); 
				heights[n+1] =d;
				break;
			}
			else {
				heights[n] = 0;
				heights[n+1] = 0;
			}
		}
		n+=2;
	}
}
int Player::getAmmo()
{
	return ammo;
}
void Player::enemycast(std::vector<double>& res, std::vector<Enemy*>& enm) {
	res.clear();
	for (Enemy* i : enm) {
		double xl = i->getX() - x;
		double yl = i->getY() - y;
		double l = sqrt(pow(xl, 2) + pow(yl, 2));
		double ang =(yl <= 0 ? acos(xl / l) : 2 * M_PI - acos(xl / l)) - angle;
		if (l < 600 && ang < M_PI /6) {
			res.push_back((-ang + M_PI / 6) / (M_PI / 3));
			res.push_back((600-l) / 600);
		}
	}
}
double Player::getAngle()
{
	return angle;
}
