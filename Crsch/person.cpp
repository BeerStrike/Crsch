#include "person.h"

Person::Person(Map* mp,int xn,int yn,int h):map(mp),x(xn),y(yn),hp(h)
{
}
int Person::getX()
{
	return  static_cast<int>(x);
}

int Person::getY()
{
	return static_cast<int>(y);
}

bool Person::getDamage(int dmg)
{
	hp -= dmg;
	return hp <= 0;
}

int Person::getHP()
{
	return hp;
}


