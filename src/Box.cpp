# include <cstring>
#include "GameEngine.hpp"
#include "Box.hpp"

Box::Box(int x, int y, eType type, t_gameinfo &gameInfo)
  : AEntity(x, y, type, gameInfo)
{
  _facto = ItemFactory::getInstance();
}

Box::~Box()
{
}

void	Box::takeDamages(int)
{
  spawnItem(_gameInfo);
  _gameInfo.map.removeEntityByPtr(this);
  _gameInfo.map.pushToCollector(this);
}

int	Box::getpSize(const int *tab, int size) const
{
  int	psize = 0;

  for (int i = 0; i < size; ++i)
    if (tab[i] != -1)
      ++psize;
  return (psize);
}

int	Box::getMaxProb(const int *tab, int size) const
{
  int	max = -1;

  for (int i = 0; i < size; ++i)
    {
      if (max == -1 || tab[i] > tab[max])
	max = i;
    }
  return (max);
}

bool	Box::sameProb(int *tab, int size) const
{
  int	tsize;
  int	num = -1;

  for (int i = 0; i < size; ++i)
    {
      if (num == -1 && tab[i] != -1)
	num = tab[i];
      else if (tab[i] != -1 && tab[i] != num)
	return (false);
    }
  while ((tsize = getpSize(tab, size)) > 1)
    tab[std::rand() % tsize] = -1;
  return (true);
}

void	Box::spawnItem(t_gameinfo &gameInfo)
{
  int		ptab[] = {PSPEED, PHEALTH}; // needs to be in the same order as AEntity enum
  int		objsize = sizeof(ptab) / sizeof(int);
  int		objtab[objsize];
  unsigned int	j = 0;
  unsigned int	i;
  int		randnum;

  std::memset(objtab, -1, sizeof(objtab));
  randnum = std::rand() % 100;
  for (i = 0; i < sizeof(ptab) / sizeof(int); ++i)
    if (randnum <= ptab[i])
      {
	std::cout << "SAVE: " << ptab[i] << std::endl;
	objtab[j++] = ptab[i];
      }
  if (objtab[0] == -1)
    i = getMaxProb(ptab, sizeof(ptab) / sizeof(int));
  else
    {
      while (getpSize(objtab, objsize) > 1)
	{
	  randnum = std::rand() % (objtab[getMaxProb(objtab, objsize)] + 1);
	  for (int i = 0; i < objsize; ++i)
	    {
	      if (objtab[i] > randnum)
		objtab[i] = -1;
	    }
	  if (sameProb(objtab, objsize))
	    break ;
	}
      i = getMaxProb(objtab, objsize);
    }
  gameInfo.map.addEntity(_facto->getItem(static_cast<eType>(SPEEDITEM + i), _x, _y));
}
