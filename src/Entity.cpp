#include "Map.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, eType type, IObject *model) : AEntity(x, y, type, model)
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

void	Entity::update(t_gameinfo &gameInfo)
{

}
