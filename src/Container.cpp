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
  v_Entcit	it = _staticEnt.begin();
  l_Entcit	lit = _mobileEnt.begin();

  _mutex->lock();
  for (v_Entcit end = _staticEnt.end(); it != end; ++it)
    if ((*it)->getXPos() == x && (*it)->getYPos() == y)
      {
	_mutex->unlock();
	return ((*it)->getType());
      }
  _mutex->unlock();
  for (l_Entcit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
      return ((*lit)->getType());
  return (FREE);
}

void	Container::stockEntity(AEntity *ent)
{
  if (ent->getType() == WALL)
    _staticEnt.push_back(ent);
  else
    _mobileEnt.push_back(ent);
}

void	Container::removeContBlock(int x, int y)
{
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
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  _mutex->lock();
  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
      {
	_mutex->unlock();
	return (*lit);
      }
  _mutex->unlock();
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y)
      return (*vit);
  return (NULL);
}

AEntity		*Container::getEntityIf(int x, int y, eType value)
{
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  _mutex->lock();
  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	(*lit)->getType() == value)
      {
	_mutex->unlock();
	return (*lit);
      }
  _mutex->unlock();
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() == value)
      return (*vit);

  return (NULL);
}

AEntity		*Container::getEntityIfNot(int x, int y, eType value)
{
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

  _mutex->lock();
  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	(*lit)->getType() != value)
      {
	_mutex->unlock();
	return (*lit);
      }
  _mutex->unlock();
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() != value)
      return (*vit);
  return (NULL);
}
