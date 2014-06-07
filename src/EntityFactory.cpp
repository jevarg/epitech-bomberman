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
  std::pair<std::map<eType, AEntity *>::iterator, bool> ret;

  ret = _items.insert(std::pair<eType, AEntity *>(type, item));
  if (ret.second == false)
    delete (item);	// means it has already been inserted
}

AEntity	*EntityFactory::getEntity(eType type, int x, int y)
{
  std::cout << type << std::endl;
  return (_items[type]->clone(x, y));
}
