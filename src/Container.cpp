#include "Container.hpp"

Container::Container()
{
}

Container::~Container()
{
}

eType	Container::checkContColision(int x, int y) const
{
  v_Entcit	it = _staticEnt.begin();
  l_Entcit	lit = _mobileEnt.begin();

  for (v_Entcit end = _staticEnt.end(); it != end; ++it)
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
    _staticEnt.push_back(ent);
  else
    _mobileEnt.push_back(ent);
}

void	Container::removeContBlock(int x, int y)
{
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->_x == x && (*lit)->_y == y)
	{
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

void		Container::setMobilEnt(int x, int y, eType type)
{
  l_Entit	lit = _mobileEnt.begin();

  for (l_Entit end = _mobileEnt.end(); lit != end; ++lit)
    {
      if ((*lit)->_x == x && (*lit)->_y == y)
	{
	  if (type == FREE)
	    _mobileEnt.erase(lit);
	  else
	    (*lit)->_type = type;
	  return ;
	}
    }  
}
