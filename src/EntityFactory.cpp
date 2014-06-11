#include "EntityFactory.hpp"

EntityFactory EntityFactory::_facto = EntityFactory();

EntityFactory *EntityFactory::getInstance()
{
  return (&_facto);
}

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

void	EntityFactory::addEntity(eType type, AEntity *item)
{
  _items[type] = item;
}

AEntity	*EntityFactory::getEntity(eType type, int x, int y)
{
  return (_items[type]->clone(x, y));
}
