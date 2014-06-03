#include "Item.hpp"

Item::Item(int x, int y, t_gameinfo &gameInfo) :
  AItem(x, y, ITEM, gameInfo)
{
}

Item::~Item()
{
}

void	Item::setAttr(ACharacter *ch) const
{
  (void)ch;
}

AItem	*Item::clone(int x, int y)
{
  return (new Item(x, y, _gameInfo));
}
