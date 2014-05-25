#include "Container.hpp"

Container::Container()
{
  _mutex = new Mutex();
}

Container::~Container()
{
  delete (_mutex);
}

eType	Container::checkColision(int x, int y) const
{
  Scopelock	<Mutex>sc(*_mutex);
  v_Entcit	it = _staticEnt.begin();
  l_Entcit	lit = _mobileEnt.begin();

  for (v_Entcit end = _staticEnt.end(); it != end; ++it)
    if ((*it)->getXPos() == x && (*it)->getYPos() == y)
      return ((*it)->getType());
   for (l_Entcit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
      return ((*lit)->getType());
  return (FREE);
}

void	Container::stockEntity(AEntity *ent)
{
  Scopelock	<Mutex>sc(*_mutex);
  if (ent->getType() == WALL)
    _staticEnt.push_back(ent);
  else
    _mobileEnt.push_back(ent);
}

void	Container::removeContBlock(int x, int y)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
	{
	  _mobileEnt.erase(lit);
	  return ;	       	// Here i consider one object get erased by case.
	}
    }
}

void	Container::removeContBlockByPtr(AEntity *ptr)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if (*lit == ptr)
	{
	  *lit = NULL;
	  _mobileEnt.erase(lit);
	  return ;	       	// Here i consider one object get erased by case.
	}
    }
}

v_Entcit	Container::vecBegin() const
{
  return (_staticEnt.begin());
}

v_Entcit	Container::vecEnd() const
{
  return (_staticEnt.end());
}

l_Entcit	Container::listBegin() const
{
  return (_mobileEnt.begin());
}

l_Entcit	Container::listEnd() const
{
  return (_mobileEnt.end());
}

l_Entit	Container::listBeginMod()
{
  return (_mobileEnt.begin());
}

l_Entit	Container::listEndMod()
{
  return (_mobileEnt.end());
}

AEntity		*Container::getEntity(int x, int y)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  _mutex->lock();
  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y)
      return (*vit);
  return (NULL);
}

AEntity		*Container::getEntityIf(int x, int y, eType value)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	(*lit)->getType() == value)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() == value)
      return (*vit);

  return (NULL);
}

AEntity		*Container::getEntityIfNot(int x, int y, eType value)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	(*lit)->getType() != value)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() != value)
      return (*vit);
  return (NULL);
}

Mutex	*Container::getMutex() const
{
  return (_mutex);
}
