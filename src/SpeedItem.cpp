#include "SpeedItem.hpp"

SpeedItem::SpeedItem(int x, int y, eType type, t_gameinfo &gameInfo) :
  AItem(x, y, type, gameInfo)
{
  _amount = SPEED_AMOUNT;
}

SpeedItem::~SpeedItem()
{
}

void	SpeedItem::setAttr(ACharacter *ch) const
{
  if (ch->getSpeed() < SPEED_MAX)
    ch->setSpeed(ch->getSpeed() + _amount);
}
