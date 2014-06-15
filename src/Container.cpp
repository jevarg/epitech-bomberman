#include "Container.hpp"

Container::Container()
{
<<<<<<< HEAD
  _mutex = new Mutex();
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Container::~Container()
{
<<<<<<< HEAD
  delete (_mutex);
}

eType	Container::checkColision(int x, int y) const
{
  Scopelock	<Mutex>sc(*_mutex);
=======
}

eType	Container::checkContColision(int x, int y) const
{
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  v_Entcit	it = _staticEnt.begin();
  l_Entcit	lit = _mobileEnt.begin();

  for (v_Entcit end = _staticEnt.end(); it != end; ++it)
<<<<<<< HEAD
    if ((*it)->getXPos() == x && (*it)->getYPos() == y &&
	(*it)->toDestroy() == false)
      return ((*it)->getType());
   for (l_Entcit end = _mobileEnt.end(); lit != end; ++lit)
     if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	 (*lit)->toDestroy() == false)
       return ((*lit)->getType());
   return (FREE);
}

void	Container::stockEntity(AEntity *ent)
{
  Scopelock	<Mutex>sc(*_mutex);

  if (ent->getType() == WALL)
=======
    if ((*it)->_x == x && (*it)->_y == y)
      return ((*it)->_type);
  for (l_Entcit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->_x == x && (*lit)->_y == y)
      return ((*lit)->_type);
  return (FREE);
}

void	Container::stockEntitie(t_entity *ent)
{
  if (ent->_type == WALL)
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
    _staticEnt.push_back(ent);
  else
    _mobileEnt.push_back(ent);
}

void	Container::removeContBlock(int x, int y)
{
<<<<<<< HEAD
  Scopelock	<Mutex>sc(*_mutex);
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
<<<<<<< HEAD
      if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
=======
      if ((*lit)->_x == x && (*lit)->_y == y)
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
	{
	  _mobileEnt.erase(lit);
	  return ;	       	// Here i consider one object get erased by case.
	}
    }
}

<<<<<<< HEAD
/*
** /!\ Never put *lit or *vit to NULL, else this of obj wil be set to NULL
*/

void	Container::removeContBlockByPtr(AEntity *ptr)
{
  Scopelock	<Mutex>sc(*_mutex);
  l_Entit	lit = _mobileEnt.begin();
  v_Entit	vit = _staticEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if (*lit == ptr)
	{
	  _mobileEnt.erase(lit);
	  return ;	       	// Here i consider one object get erased by case.
	}
    }
  /*
  ** Better check the static position after
  ** Will normaly only be called on game destruction
  */
  for (v_Entit end = _staticEnt.end(); vit != end; ++vit)
    {
      if (*vit == ptr)
	{
	  _staticEnt.erase(vit);
	  return ;	       	// Here i consider one object get erased by case.
	}
    }
}

=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
v_Entcit	Container::vecBegin() const
{
  return (_staticEnt.begin());
}

v_Entcit	Container::vecEnd() const
{
  return (_staticEnt.end());
}

<<<<<<< HEAD
v_Entit	Container::vecBeginMod()
{
  return (_staticEnt.begin());
}

v_Entit	Container::vecEndMod()
{
  return (_staticEnt.end());
}

AEntity	*Container::vecFront() const
{
  Scopelock	<Mutex>sc(*_mutex);

  return (_staticEnt.empty() ? NULL : _staticEnt.front());
}

bool	Container::vecEmpty() const
{
  return (_staticEnt.empty());
}

AEntity	*Container::listFront() const
{
  Scopelock	<Mutex>sc(*_mutex);

  return (_mobileEnt.empty() ? NULL : _mobileEnt.front());
}

bool	Container::listEmpty() const
{
  return (_mobileEnt.empty());
}

=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
l_Entcit	Container::listBegin() const
{
  return (_mobileEnt.begin());
}

l_Entcit	Container::listEnd() const
{
  return (_mobileEnt.end());
}
<<<<<<< HEAD

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

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	(*lit)->toDestroy() == false)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->toDestroy() == false)
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
	IFCHARACTER((*lit)->getType(), value) && (*lit)->toDestroy() == false)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() == value && (*vit)->toDestroy() == false)
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
	IFNOTCHARACTER((*lit)->getType(), value) && (*lit)->toDestroy() == false)
      return (*lit);
  for (v_Entcit end = _staticEnt.end(); vit != end; ++vit)
    if ((*vit)->getXPos() == x && (*vit)->getYPos() == y &&
	(*vit)->getType() != value && (*vit)->toDestroy() == false)
      return (*vit);
  return (NULL);
}

Mutex	*Container::getMutex() const
{
  return (_mutex);
}
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
