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
