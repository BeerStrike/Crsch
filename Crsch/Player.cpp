#define _USE_MATH_DEFINES
#include "Player.h"
#include <cmath>
Player::Player(Map* mp):Person(mp, mp->getPlayerX() * 100 + 50, mp->getPlayerY() * 100 + 50)
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

void Player::shot(std::vector<Enemy*>&enm)
{
	std::vector<Enemy*>::iterator i = enm.begin();
	while(i!=enm.end()) {
		if (sqrt(pow((*i)->getX() - x, 2) + pow((*i)->getY() - y, 2)) < 400) {
			std::vector<Enemy*>::iterator dl = i;
			i++;
			enm.erase(dl);
		//	if (i == enm.end())
		//		break;
		}else i++; 
	}
}

double* Player::raycast(int num, std::vector<Enemy*>&enm)
{
	double* heights=new double[2*num];
	double step = (M_PI / 3) / num;
	int n = 0;
	double mgs =600;
	for (double i = angle+M_PI / 6; i > angle-M_PI / 6; i -= step) {
		for (int j = 0; j < mgs; j+=10) {
			int xm = (x + j * cos(i)) / 100;
			int ym = (y +  - j * sin(i)) / 100;
			if (map->at(xm, ym) == 3) {
				map->setCell(xm, ym, 0);
				enm.push_back(new Enemy(map, this, xm , ym));
			}
			if (map->at(xm, ym) == 1) {
				while (map->at(xm, ym) == 1) {
					xm = (x + j * cos(i)) / 100;
					ym = (y + -j * sin(i)) / 100;
					j--;
				}
				j++;
				double nw = pow((mgs - j) / mgs,2);
				heights[n] = nw*cos(i-angle); 
				break;
			}
		}
		n++;
	}
	return heights;
}
double* Player::enemycast(int num, std::vector<Enemy*>& enm) {
	double* res = new double [2*enm.size()+1];
	int cnt = 0;
	for (Enemy* i : enm) {
		if (abs(atan(tan(angle+M_PI/2)) - atan(abs((i->getX() - x) / (i->getY() - y)))) < M_PI / 6) {
			res[cnt] = (400-sqrt(pow((i->getX() - x), 2) + pow((i->getY() - y), 2))) / 400;
			res[cnt + 1] = (atan(tan(angle + M_PI / 2)) - atan(abs((i->getX() - x) / (i->getY() - y)))) + (M_PI / 6) / (M_PI / 3);
			cnt+=2;
		}
			
	}
	res[cnt] = -1;
	return res;
}
double Player::getAngle()
{
	return angle;
}
