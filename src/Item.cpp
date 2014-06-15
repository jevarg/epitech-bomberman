#include "Item.hpp"

<<<<<<< HEAD
Item::Item(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, ITEM, gameInfo, thread)
{
=======
Item::Item(eItemType itemType)
  : _itemType(itemType)
{  
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Item::~Item()
{
<<<<<<< HEAD
}

void	Item::setAttr(ACharacter */*ch*/) const
{
}

AItem	*Item::clone(int x, int y)
{
  return (new Item(x, y, _gameInfo));
=======

}

eItemType	Item::getType() const
{
  return (_itemType);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}
