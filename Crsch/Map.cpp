#include "Map.h"

Map::Map(std::ifstream& fin)
{
    fin >> size;
    map = new int* [size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
        for (int j = 0; j < size; j++)
            fin >> map[i][j];
    }
    fin.close();
}

Map* Map::make(std::string str)
{
    std::ifstream fin(str);
    if (fin)
        return new Map(fin);
    else
    return nullptr;
}

int Map::at(int x, int y)
{
    return  map[x][y];
}

int Map::getSize()
{
    return size;
}

Map::~Map()
{
    for (int i = 0; i < size; i++)
        delete[] map[i];
    delete[] map;
}
