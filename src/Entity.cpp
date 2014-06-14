#include "GameEngine.hpp"
#include "Map.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, eType type, t_gameinfo *gameInfo) :
  AEntity(x, y, type, gameInfo)
{
}

Entity::~Entity()
{
}

void	Entity::takeDamages(int)
{
}

AEntity *Entity::clone(int x, int y)
{
  return (new Entity(x, y, _type, _gameInfo));
}
