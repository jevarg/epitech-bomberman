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
  _density = 30;	// expressed in %
  _linear = 40;
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
  equa[0] = (_map[(y + 1) * _mapX + x] == FREE);
  equa[1] = (_map[(y - 1) * _mapX + x] == FREE);
  equa[2] = (_map[y * _mapX + (x + 1)] == FREE);
  equa[3] = (_map[y * _mapX + (x - 1)] == FREE);
  for (int i = 0; i < 4 && counter < 2; ++i)
    counter += equa[i];
  return (counter == 2 ? false : true);
}

short	Map::getDir(bool *rtab, short cuBlock) const
{
  short		dir = 0;
  bool		tab[4] = {rtab[0], rtab[1], rtab[2], rtab[3]};

  if (!tab[(cuBlock + 2) % 4] && ((std::rand() & 0xFFFF) % 100) < _linear)
    return ((cuBlock + 2) % 4);
  for (short i = 0; i < 4; ++i)
    if (!tab[i])
      ++dir;
  if (dir > 1)
    {
      tab[(cuBlock + 2) % 4] = true;
      --dir;
    }
  else if (dir == 0)
    return (-1);
  dir = std::rand() % dir;
  for (short i = 0; i < 4; ++i)
    {
      if (!tab[i] && dir <= 0)
	return (i);
      else if (!tab[i] && dir > 0)
	--dir;
    }
  return (-1);
}

/*
**
** Recursive Backtracker
**
*/

void	Map::genSmallMaze(short x, short y, short pos)
{
  short	dir;
  short	tx;
  short	ty;
  bool 	tabdir[4] = {false, false, false, false};

  _map[y * _mapX + x] = FREE;
  if (pos < 4)
    tabdir[pos] = true;
  while (!tabdir[0] || !tabdir[1] || !tabdir[2] || !tabdir[3])
    {
      tx = x;
      ty = y;
      if ((dir = getDir(tabdir, pos)) == -1)
	return ;
      tabdir[dir] = true;
      tx += (dir == WEST) ? -1 : (dir == EAST) ? 1 : 0;
      ty += (dir == SOUTH) ? 1 : (dir == NORTH) ? -1 : 0;
      if (checkValidPath(tx, ty) == true)
	genSmallMaze(tx, ty, (dir + 2) % 4);
    }
}

/*
**
** Hunt & Kill
**
*/

void	Map::genBigMaze()
{
  unsigned int	i;
  unsigned int	max = (_mapY - 1) * _mapX;

  for (i = _mapX; i < max; ++i)
    {
      if (i % _mapX == 0 || (i + 1) % _mapX == 0)
	continue ;
      if ((i / _mapX) % 2 != 0)
	{
	  if (std::rand() % 100 < _density / 4)
	    _map[i] = BOX;
	  else
	    _map[i] = FREE;
	}
      else if (i % 2 != 0)
	_map[i] = FREE;
    }
}

void	Map::display()
{
  int	totalsize = _mapX * _mapY;

  for (int i = 0; i < totalsize; ++i)
    {
      if (i != 0 && i % (_mapX ) == 0)
	std::cout << std::endl;
      std::cout << (_map[i] == WALL ? "x" : (_map[i] == BOX) ? "B" : " ");
    }
  std::cout << std::endl;
}

bool	Map::checkAccess(short x, short y) const
{
  char	sumX[4] = {0,0,1,-1};
  char	sumY[4] = {1,-1,0,0};
  eType	tmp;
  short	counter = 0;

  for (unsigned short i = 0; i < 4; ++i)
    {
      tmp = _map[(y + sumY[i]) * _mapX + (x + sumX[i])];
      if (tmp == FREE || tmp == BOX)
	++counter;
    }
  return (counter >= 1 ? true : false);
}

void	Map::fillBox()
{
  unsigned int	totalsize = _mapX * _mapY;
  short	x;
  short	y;

  for (unsigned int i = 0; i < totalsize; ++i)
    {
      y = i / _mapX;
      x = i % _mapX;
      if (y == _mapY - 1 || y == 0 || x == 0 || x == _mapX - 1)
	continue ;
      if (_map[i] == WALL && checkAccess(x, y) &&
	  std::rand() % 100 < _density)
	_map[i] = BOX;
    }
}

void	Map::fillContainers()
{
  unsigned int	i;
  t_entity	*ent;
  unsigned int 	totalsize = _mapX * _mapY;

  for (i = 0; i < totalsize; ++i)
    {
      if (_map[i] != FREE) // means there is no block
	{
	  ent = new t_entity(i % _mapX, i /_mapX, _map[i]);
	  addEntitie(ent);
	}
    }
  _map.clear();	// erase the temps vector
}

void	Map::removeEntity(int x, int y)
{
  unsigned int	pos = getContPos(x, y);

  _cont[pos]->removeContBlock(x, y);
}

void	Map::createMap()
{
  int	posx;
  int	posy;
  int	totalsize = _mapX * _mapY;

  std::srand(std::time(NULL));
  for (int i = 0; i < totalsize; ++i)
    _map.push_back(WALL);
  posx = 2 + std::rand() % (_mapX - 3);
  posy = 2 + std::rand() % (_mapY - 3);
  std::cout << "Starting at " << posx << " " << posy << std::endl;
  if (_mapX * _mapY > MAXSIZE)
    genBigMaze();
  else
    genSmallMaze(posx, posy, 4);
  fillBox();
  fillContainers();
  display();
}

unsigned int	Map::getContPos(int x, int y) const
{
  unsigned int	ratiox;
  unsigned int	ratioy;

  ratiox = x / SQUARESIZE;
  ratioy = y / SQUARESIZE;
  return (ratioy * (_mapX / SQUARESIZE) + ratiox);
}

void	Map::addEntitie(t_entity *ent)
{
  unsigned int	pos;
  Container	*cont;

  pos = getContPos(ent->_x, ent->_y);
  while (_cont.size() <= pos)
    {
      cont = new Container;
      _cont.push_back(cont);
    }
  _cont[pos]->stockEntitie(ent);
}

eType	Map::checkMapColision(int x, int y) const
{
  unsigned int	pos = getContPos(x, y);

  return (_cont[pos]->checkContColision(x, y));
}

int	Map::getWidth() const
{
  return (_mapX);
}

int	Map::getHeight() const
{
  return (_mapY);
}

v_Contcit	Map::ContBegin() const
{
  return (_cont.begin());
}

v_Contcit	Map::ContEnd() const
{
  return (_cont.end());
}
