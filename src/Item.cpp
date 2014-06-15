#include "Item.hpp"

Item::Item(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, ITEM, gameInfo, thread)
{
}

Item::~Item()
{
}

void	Item::setAttr(ACharacter */*ch*/) const
{
}

AItem	*Item::clone(int x, int y)
{
  return (new Item(x, y, _gameInfo));
}
