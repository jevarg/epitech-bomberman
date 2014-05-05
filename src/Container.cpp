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

void	Container::stockEntitie(AEntitie *ent)
{
  if (ent->getType() == WALL)
    _staticEnt.push_back(ent);
  else
    _mobileEnt.push_back(ent);
}
