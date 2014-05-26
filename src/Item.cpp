#include "Item.hpp"

Item::Item(int x, int y, eType type, t_gameinfo &gameInfo) :
  AItem(x, y, type, gameInfo)
{
}

Item::~Item()
{
}

void	Item::setAttr(ACharacter *ch) const
{
  (void)ch;
}
