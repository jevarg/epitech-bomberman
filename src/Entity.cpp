#include "Map.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, eType type) : AEntity(x, y, type)
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

bool	Entity::update(gdl::Clock const &clock, Input const &input, Map &map)
{
  return (false);
}
