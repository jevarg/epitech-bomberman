#include "ItemFactory.hpp"

ItemFactory ItemFactory::_facto = ItemFactory();

ItemFactory *ItemFactory::getInstance()
{
  return (&_facto);
}

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

void	ItemFactory::addItem(eType type, AItem *item)
{
  std::pair<std::map<eType, AItem *>::iterator, bool> ret;

  ret = _items.insert(std::pair<eType, AItem *>(type, item));
  if (ret.second == false)
    delete (item);	// means it has already been inserted
}

AItem	*ItemFactory::getItem(eType type, int x, int y)
{
  return (_items[type]->clone(x, y));
}
