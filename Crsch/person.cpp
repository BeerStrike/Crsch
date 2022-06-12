#include "person.h"

Person::Person(Map* mp,int xn,int yn)
{
	map = mp;
	x = xn;
	y = yn;
}
int Person::getX()
{
	return  static_cast<int>(x);
}

int Person::getY()
{
	return static_cast<int>(y);
}
