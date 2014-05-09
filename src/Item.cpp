#include "Item.hpp"

Item::Item(eItemType itemType)
  : _itemType(itemType)
{  
}

Item::~Item()
{

}

eItemType	Item::getType() const
{
  return (_itemType);
}
