#include "GameEngine.hpp"
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
  if (ch->getSpeed() < SPEED_MAX)
    ch->setSpeed(ch->getSpeed() + _amount);
  _gameInfo.sound.playSound("orb");
}

AItem	*SpeedItem::clone(int x, int y)
{
  return (new SpeedItem(x, y, _gameInfo));
}
