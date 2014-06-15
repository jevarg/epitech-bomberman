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
  for (std::map<eType, AEntity *>::iterator it= _items.begin(); it != _items.end(); it++)
    if (it->first != CHARACTER2 && it->first != CHARACTER1)
      delete (it->second);
}

void	EntityFactory::addEntity(eType type, AEntity *item)
{
  _items[type] = item;
}

AEntity	*EntityFactory::getEntity(eType type, int x, int y)
{
  return (_items[type]->clone(x, y));
}
