#include "SpeedItem.hpp"

SpeedItem::SpeedItem(int x, int y, t_gameinfo &gameInfo) :
  AItem(x, y, SPEEDITEM, gameInfo)
{
  _amount = SPEED_AMOUNT;
}

SpeedItem::~SpeedItem()
{
}

void	SpeedItem::setAttr(ACharacter *ch) const
{
  ch->setSpeed(ch->getSpeed() + _amount);
}

AItem	*SpeedItem::clone(int x, int y)
{
  return (new SpeedItem(x, y, _gameInfo));
}
