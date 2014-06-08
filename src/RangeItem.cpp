#include "GameEngine.hpp"
#include "RangeItem.hpp"

RangeItem::RangeItem(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, SPEEDITEM, gameInfo, thread)
{
  _amount = SPEED_AMOUNT;
}

RangeItem::~RangeItem()
{
}

void	RangeItem::setAttr(ACharacter *ch) const
{
  ch->setRange(ch->getRange() + _amount);
  //_gameInfo->sound->playSound("orb");
}

AItem	*RangeItem::clone(int x, int y)
{
  return (new RangeItem(x, y, _gameInfo));
}
