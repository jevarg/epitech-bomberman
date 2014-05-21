#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cmath>
#include "Map.hpp"

Map::Map(Settings &set)
{
  _mapX = set.getVar(MAP_HEIGHT);
  _mapY = set.getVar(MAP_WIDTH);
  _density = set.getVar(MAP_DENSITY);	// expressed in %
  _linear = set.getVar(MAP_LINEAR);
  std::cout << _density << " " << _linear << std::endl;
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

bool		Map::load(Settings &settings, const std::string &name, std::map<eType, IObject *> &type)
{
  std::ifstream	file(name.c_str());
  std::string	buf;
  unsigned int	len = 0;
  int		y = 0;
  int		x = 0;

  if ((file.rdstate() && std::ifstream::failbit) != 0)
    {
      std::cerr << "Error while loading map, couldn't open : " << name << std::endl;
      return (false);
    }
  while (std::getline(file, buf))
    {
      x = 0;
      if (len == 0)
	len = buf.length();
      else
	if (len != buf.length())
	  {
	    std::cerr << "Error while loading map on line : " << y << std::endl;
	    return (false);
	  }
      for (std::string::const_iterator it = buf.begin(); it != buf.end(); ++it)
	{
	  switch (*it)
	    {
	    case 'W':
	      addEntity(new Entity(x, y, WALL, type[WALL]->clone()));
	      break;
	    case 'B':
	      addEntity(new Entity(x, y, BOX, type[BOX]->clone()));
	      break;
	    case ' ':
	      break;
	    default:
	      std::cerr << "Error while loading map on line : " << y << " column : " << x << std::endl;
	      return (false);
	    }
	  ++x;
	}
      ++y;
    }
  settings.setVar(MAP_HEIGHT, y);
  settings.setVar(MAP_WIDTH, x);
  return (true);
}

bool		Map::save(const std::string &name)
{
  std::ofstream	file(name.c_str());
  std::string	buf;

  for (int y = 0; y < _mapY; ++y)
    {
      buf = "";
      for (int x = 0; x < _mapX; ++x)
	{
	  switch (checkMapColision(x, y))
	    {
	    case WALL:
	      buf.insert(x, 1, 'W');
	      break;
	    case BOX:
	      buf.insert(x, 1, 'B');
	      break;
	    default:
	      buf.insert(x, 1, ' ');
	    }
	}
      file << buf << "\n";
    }
  return (true);
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

  std::cout << x << " " << y << " " << _mapX << std::endl;
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
  eType	t;

  for (int i = 0; i < totalsize; ++i)
    {
      if ((t = checkMapColision(i % _mapX, i / _mapX)) == WALL)
	std::cout << "x";
      else if (t == BOX)
	std::cout << "B";
      else if (t == FREE)
	std::cout << " ";
      else if (t == CHARACTER)
	std::cout << "C";
      else
	std::cout << "?";
      if (i != 0 && i % _mapX == _mapX - 1)
	std::cout << std::endl;
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

void	Map::fillContainers(std::map<eType, IObject *> &type)
{
  unsigned int	i;
  unsigned int 	totalsize = (_mapY - 1) * _mapX;
  ModelFactory  &fact = ModelFactory::getInstance();

  for (i = _mapX; i < totalsize; ++i)
    {
      // means there is a block & It's not the border
      if (_map[i] != FREE && (i % _mapX != 0 && (i + 1) % _mapX != 0))
	addEntity(new Entity(i % _mapX, i /_mapX, _map[i], fact.getModel(_map[i])));
    }
  _map.clear();	// erase the temps vector
}

void	Map::removeEntity(int x, int y)
{
  unsigned int	pos = getContPos(x, y);

  _cont[pos]->removeContBlock(x, y);
}

void	Map::removeEntityByPtr(AEntity *ptr)
{
  unsigned int	pos = getContPos(ptr->getXPos(), ptr->getYPos());

  _cont[pos]->removeContBlockByPtr(ptr);
}

/*
** Main function
*/

void	Map::createMap(std::map<eType, IObject *> &type)
{
  int	posx;
  int	posy;
  int	totalsize = _mapX * _mapY;

  std::srand(std::time(NULL));
  for (int i = 0; i < totalsize; ++i)
    _map.push_back(WALL);
  posx = 2 + std::rand() % (_mapX - 3);
  posy = 2 + std::rand() % (_mapY - 3);
  if (_mapX * _mapY > MAXSIZE)
    genBigMaze();
  else
    genSmallMaze(posx, posy, 4);
  fillBox();
  fillContainers(type);
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

void	Map::addEntity(AEntity *ent)
{
  unsigned int	pos;
  Container	*cont;

  pos = getContPos(ent->getXPos(), ent->getYPos());
  while (_cont.size() <= pos)
    {
      cont = new Container;
      _cont.push_back(cont);
    }
  _cont[pos]->stockEntity(ent);
}

/*
** The condition pos >= _cont.size() is only used when a region isn't mapped
** It could happen if the SQUARESIZE is very small (1 or 2)
** It happens if the mapped zone has no block in a zonesize > SQUARESIZE.
*/

eType	Map::checkMapColision(int x, int y) const
{
  unsigned int	pos = getContPos(x, y);

  if (y == 0 || y == _mapY - 1 || x  == 0 || x == _mapX - 1)
    return (WALL);
  else if (pos >= _cont.size())
    return (FREE);
  return (_cont[pos]->checkColision(x, y));
}

unsigned int	Map::getWidth() const
{
  return (_mapX);
}

unsigned int	Map::getHeight() const
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

void		Map::setEntity(int x, int y, eType type)
{
  (_cont[getContPos(x, y)])->setEntity(x, y, type);
}

void		Map::setEntityIf(int x, int y, eType newValue, eType oldValue)
{
  (_cont[getContPos(x, y)])->setEntityIf(x, y, newValue, oldValue);
}

void		Map::setEntityIfNot(int x, int y, eType newValue, eType oldValue)
{
  (_cont[getContPos(x, y)])->setEntityIfNot(x, y, newValue, oldValue);
}

AEntity		*Map::getEntity(int x, int y) const
{
  return ((_cont[getContPos(x, y)])->getEntity(x, y));
}

AEntity		*Map::getEntityIf(int x, int y, eType value) const
{
  return ((_cont[getContPos(x, y)])->getEntityIf(x, y, value));
}

AEntity		*Map::getEntityIfNot(int x, int y, eType value) const
{
  return ((_cont[getContPos(x, y)])->getEntityIfNot(x, y, value));
}
