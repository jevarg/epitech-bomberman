#include <cstring>
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
    _gameInfo->sound->play("box", EFFECT);
  }
}

int	Box::getpSize(const double *tab, int size) const
{
  int	psize = 0;

  for (int i = 0; i < size; ++i)
    {
      if (tab[i] != -1)
	++psize;
    }
  return (psize);
}

double	Box::getMaxProb(const double *tab, int size) const
{
  int	max = -1;

  for (int i = 0; i < size; ++i)
    {
      if (max == -1 || tab[i] > tab[max])
	max = i;
    }
  return (tab[max]);
}

int	Box::getMinProbPos(const double *tab, int size) const
{
  int	min = -1;

  for (int i = 0; i < size; ++i)
    {
      if (min == -1 || (tab[i] != -1 && tab[i] < tab[min]))
	min = i;
    }
  return (min);
}

int		Box::hasSame(double * const tab, int size) const
{
  double	val;
  int		spos = -1;

  for (int i = 0; i < size; ++i)
    {
      if (tab[i] == -1)
	continue ;
      val = tab[i];
      spos = i;
      for (int j = i + 1; j < size; j++)
	{
	  if (tab[j] == val)
	    return (spos);
	}
    }
  return (-1);
}

void		Box::selectSameProb(double * const tab, int size) const
{
  int		countSame;
  int		localCount;
  int		pos;
  double	val;
  int		nb;

  while ((pos = hasSame(tab, size)) != -1)
    {
      val = -1;
      countSame = 0;
      localCount = 0;

      for (int i = pos; i < size; ++i)
	{
	  if (val == -1 && tab[i] != -1)
	    val = tab[i];
	  if (tab[i] != -1 && tab[i] == val)
	    ++countSame;
	}
      while (countSame > 1)
	{
	  nb = 1 + std::rand() % countSame; // Will define witch number will be removed
	  for (int i = pos; i < size;)
	    {
	      if (tab[i] == val)
		++localCount;
	      if (localCount == nb)
		{
		  tab[i] = -1;
		  break ;
		}
	      ++i;
	    }
	  --countSame;
	}
    }
}

void	Box::scaleToPercent(double * const tab, int size) const
{
  int		total = 0;
  double	ratio;

  for (int i = 0; i < size; ++i)
    total += tab[i];
  ratio = total / 100.0;
  for (int i = 0; i < size; ++i)
    tab[i] /= ratio;
}

void	Box::spawnItem()
{
  // needs to be in the same order as AEntity enum
  double       	ptab[] = {PCHICKEN, PSPEED, PHEALTH, PSTOCK, PRANGE, PEMPTY};
  int		size = sizeof(ptab) / sizeof(double);
  int		randnum;
  double       	start = 0;
  EntityFactory *facto = EntityFactory::getInstance();

  randnum = std::rand() % 100;
  scaleToPercent(ptab, size);
  for (int i = 0; i < size; ++i)
    {
      if (start + ptab[i] > randnum) // means randnum is in the concerned area
	{
	  if (i == size - 1)
	    return ;
	  _gameInfo->map->addEntity(facto->getEntity
				    (static_cast<eType>(CHICKEN + i), _x, _y));
	  break ;
	}
      if (ptab[i] != -1)
	start += ptab[i];
    }
}

AEntity *Box::clone(int x, int y)
{
  return (new Box(x, y, _gameInfo));
}
