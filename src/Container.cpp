#include "Container.hpp"

Container::Container()
{
}

Container::~Container()
{
}

bool	Container::checkColision()
{
  return (false);
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
