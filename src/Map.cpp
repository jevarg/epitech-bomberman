#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include "Map.hpp"

Map::Map()
{
}

Map::~Map()
{
}

void	Map::generateMaze(int x, int y)
{
  int		dir = 5;
  int		tx;
  int		ty;

  for (int i = 0; i < 4 && dir == 5; ++i)
    {
      tx = x;
      ty = y;
      dir = std::rand() % 4;
      tx += (dir == WEST) ? -1 : (dir == EAST) ? 1 : 0;
      ty += (dir == SOUTH) ? 1 : (dir == NORTH) ? -1 : 0;
    }
  generateMaze(x, y);
}

void	Map::createMap()
{
  int	posx;
  int	posy;
  int	totalsize = _mapX * _mapY;

  std::srand(std::time(NULL));
  for (int i = 0; i < totalsize; ++i)
    _map.push_back(FREE);
  posx = std::rand() % (_mapX - 1) + 1;
  posy = std::rand() % (_mapY - 1) + 1;
  generateMaze(posx, posy);
}

int	Map::getWidth() const
{
  return (_mapX);
}

int	Map::getHeight() const
{
  return (_mapY);
}
