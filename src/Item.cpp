#include "Item.hpp"

Item::Item(eItemType itemType)
  : _itemType(itemType)
{
}

Item::~Item()
{

}

eItemType	Item::getItemType() const
{
  return (_itemType);
}
