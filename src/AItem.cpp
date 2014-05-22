#include "AItem.hpp"

AItem::AItem(int x, int y, eType type) :
  AEntity(x, y, type)
{
  _timeout = NO_TIMEOUT;
  _amount = 0;
}

AItem::~AItem()
{
}

void	AItem::takeDamages(int /*amount*/)
{
  _toDestroy = true;
}
