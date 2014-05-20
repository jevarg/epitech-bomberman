#include "Container.hpp"

Container::Container()
{
}

Container::~Container()
{
}

eType	Container::checkColision(int x, int y) const
{
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

void		Container::setEntity(int x, int y, eType type)
{
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->getXPos() == x && (*lit)->getYPos() == y)
	{
	  if (type == FREE)
	    _mobileEnt.erase(lit);
	  else
	    (*lit)->setType(type);
	  return ;
	}
    }
}

void		Container::setEntityIf(int x, int y, eType newValue, eType oldValue)
{
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	  (*lit)->getType() == oldValue)
	{
	  if (newValue == FREE)
	    _mobileEnt.erase(lit);
	  else
	    (*lit)->setType(newValue);
	  return ;
	}
    }
}

void		Container::setEntityIfNot(int x, int y, eType newValue, eType oldValue)
{
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->getXPos() == x && (*lit)->getYPos() == y &&
	  (*lit)->getType() != oldValue)
	{
	  if (newValue == FREE)
	    _mobileEnt.erase(lit);
	  else
	    (*lit)->setType(newValue);
	  return ;
	}
    }
}


AEntity		*Container::getEntity(int x, int y)
{
  l_Entit	lit = _mobileEnt.begin();
  v_Entcit	vit = _staticEnt.begin();

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
