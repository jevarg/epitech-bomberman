#include "GameEngine.hpp"
#include "SpeedItem.hpp"

SpeedItem::SpeedItem(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, SPEEDITEM, gameInfo, thread)
{
  _amount = SPEED_AMOUNT;
}

SpeedItem::~SpeedItem()
{
}

void	SpeedItem::setAttr(ACharacter *ch) const
{
  ch->setSpeed(ch->getSpeed() + _amount);
  _gameInfo->sound->play("orb", EFFECT);
  increaseScore(ch);
}

AItem	*SpeedItem::clone(int x, int y)
{
  return (new SpeedItem(x, y, _gameInfo));
}
