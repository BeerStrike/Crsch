#pragma once
#include <fstream>
#include <string>
class Map
{
private:
	Map(std::ifstream& fin);
	int size;
	int** map;
public:
	static Map* make(std::string);
	int at(int, int);
	int getSize();
	~Map();
};

