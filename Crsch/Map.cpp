#include "Map.h"

Map::Map(std::ifstream& fin)
{
    fin >> size;
    map = new int* [size];
    for (int i = 0; i < size; i++) {
        map[i] = new int[size];
        for (int j = 0; j < size; j++) {
            fin >> map[i][j];
            if (map[i][j] == 2) {
                startx = i;
                starty = j;
                map[i][j] = 0;
            }
        }
    }
    fin.close();
}

Map* Map::load(std::string str)
{
    std::ifstream fin(str);
    if (fin)
        return new Map(fin);
    else
    return nullptr;
}

int Map::at(int x, int y)
{
    if (x < size && y < size&&x>=0&&y>=0)
        return  map[x][y];
    else
        return 0;
}

int Map::getSize()
{
    return size;
}

int Map::getPlayerX()
{
    return startx;
}

int Map::getPlayerY()
{
    return starty;
}

void Map::setCell(int x, int y, int nw)
{
    map[x][y] = nw;
}


Map::~Map()
{
    for (int i = 0; i < size; i++)
        delete[] map[i];
    delete[] map;
}
