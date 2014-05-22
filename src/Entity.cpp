#include "Map.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, eType type, t_gameinfo &gameInfo) :
  AEntity(x, y, type, gameInfo)
{
}

Entity::~Entity()
{
}

void	Entity::destroy(Map &map)
{
  map.removeEntityByPtr(this);
  delete (this);
}

void	Entity::takeDamages(int)
{
}
