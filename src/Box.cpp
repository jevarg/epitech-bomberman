# include <cstring>
#include "GameEngine.hpp"
#include "Box.hpp"

Box::Box(int x, int y, t_gameinfo *gameInfo)
  : AEntity(x, y, BOX, gameInfo)
{
}

Box::~Box()
{
}

void	Box::takeDamages(int)
{
  if (_toDestroy == true)
    return ;
  setDestroy();
  {
    Scopelock	<Mutex>sc(*_mutex);
    spawnItem();
    _gameInfo->sound->playSound("box");
  }
}

int	Box::getpSize(const int *tab, int size) const
{
  int	psize = 0;

  for (int i = 0; i < size; ++i)
    {
      if (tab[i] != -1)
	++psize;
    }
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

int	Box::getMaxProb(const int *tab, const int *pos, int size) const
{
  int	max = -1;

  for (int i = 0; i < size; ++i)
    {
      if (max == -1 || tab[i] > tab[max])
	max = i;
    }
  return (pos[max]);
}

bool	Box::sameProb(int *tab, int size) const
{
  int	num = -1;

  for (int i = 0; i < size; ++i)
    {
      if (num == -1 && tab[i] != -1)
	num = tab[i];
      else if (tab[i] != -1 && tab[i] != num)
	return (false);
    }
  while (getpSize(tab, size) > 1)
    {
      int nb = std::rand() % size;
      tab[nb] = -1;
    }
  return (true);
}

void	Box::spawnItem()
{
  int		ptab[] = {PSPEED, PHEALTH, PSTOCK}; // needs to be in the same order as AEntity enum
  int		objsize = sizeof(ptab) / sizeof(int);
  int		objtab[objsize];
  int		objpos[objsize];
  unsigned int	j = 0;
  unsigned int	i;
  int		randnum;
  EntityFactory *facto = EntityFactory::getInstance();

  std::memset(objtab, -1, sizeof(objtab));
  randnum = std::rand() % 101;
  for (i = 0; i < sizeof(ptab) / sizeof(int); ++i)
    if (randnum <= ptab[i])
      {
	objtab[j] = ptab[i];
	objpos[j++] = i;
      }
  if (objtab[0] == -1)
    {
      sameProb(ptab, sizeof(ptab) / sizeof(int));
      i = getMaxProb(ptab, sizeof(ptab) / sizeof(int));
    }
  else
    {
      while (getpSize(objtab, objsize) > 1)
	{
	  randnum = std::rand() % 101;
	  for (int i = 0; i < objsize; ++i)
	    {
	      if (randnum > objtab[i] && objtab[i] != -1)
		{
		  objtab[i] = -1;
		  break ;
		}
	    }
	  if (sameProb(objtab, objsize))
	    break ;
	}
      i = getMaxProb(objtab, objpos, objsize);
    }
  _gameInfo->map->addEntity(facto->getEntity(static_cast<eType>(SPEEDITEM + i), _x, _y));
}

AEntity *Box::clone(int x, int y)
{
  return (new Box(x, y, _gameInfo));
}
