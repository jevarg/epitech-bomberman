#include "SpeedItem.hpp"

SpeedItem::SpeedItem() : AItem()
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
