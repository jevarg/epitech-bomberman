#include "SpeedItem.hpp"

SpeedItem::SpeedItem(int x, int y, eType type) :
  AItem(x, y, type)
{
  _amount = SPEED_AMOUNT;
}

SpeedItem::~SpeedItem()
{
}

void	SpeedItem::setSpeed(ACharacter &ch) const
{
  ch.setSpeed(ch.getSpeed() + _amount);
}
