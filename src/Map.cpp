#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include "Map.hpp"

#include "GameEngine.hpp"

Map::Map()
{
  _mapX = 50;
  _mapY = 50;
  _density = 10;	// expressed in %
}

Map::~Map()
{
}

bool	Map::checkValidPath(int x, int y) const
{
  int	counter = 0;
  bool	equa[4];

  if (y == _mapY - 1 || y == 0 || x == 0 || x == _mapX - 1)
    return (false);
  equa[0] = (_map[(y + 1) * _mapX + x] == USED);
  equa[1] = (_map[(y - 1) * _mapX + x] == USED);
  equa[2] = (_map[y * _mapX + (x + 1)] == USED);
  equa[3] = (_map[y * _mapX + (x - 1)] == USED);
  for (int i = 0; i < 4 && counter < 2; ++i)
    counter += equa[i];
  return (counter == 2 ? false : true);
}

void	Map::generateMaze(int x, int y)
{
  int		dir;
  int		tx;
  int		ty;
  bool		tabdir[4] = {false, false, false, false};

  _map[y * _mapX + x] = USED;
  for (int i = 0; i < 4; ++i)
    {
      tx = x;
      ty = y;
      do
	dir = std::rand() % 4;
      while (tabdir[dir]);
      tabdir[dir] = true;
      tx += (dir == WEST) ? -1 : (dir == EAST) ? 1 : 0;
      ty += (dir == SOUTH) ? 1 : (dir == NORTH) ? -1 : 0;
      if (checkValidPath(tx, ty) == true)
	generateMaze(tx, ty);
    }
}

void	Map::display()
{
  int	totalsize = _mapX * _mapY;

  for (int i = 0; i < totalsize; ++i)
    {
      if (i != 0 && i % (_mapX ) == 0)
	std::cout << std::endl;
      std::cout << (_map[i] == FREE ? "x" : " ");
    }
  std::cout << std::endl;
}

void	Map::createMap()
{
  int	posx;
  int	posy;
  int	totalsize = _mapX * _mapY;

  std::srand(std::time(NULL));
  for (int i = 0; i < totalsize; ++i)
    _map.push_back(FREE);
  posx = std::rand() % (_mapX - 2) + 1;
  posy = std::rand() % (_mapY - 2) + 1;
  std::cout << "Starting at " << posx << " " << posy << std::endl;
  generateMaze(posx, posy);
  display();
}

int	Map::getWidth() const
{
  return (_mapX);
}

int	Map::getHeight() const
{
  return (_mapY);
}
