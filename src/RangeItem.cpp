#include "GameEngine.hpp"
#include "RangeItem.hpp"

RangeItem::RangeItem(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, RANGEITEM, gameInfo, thread)
{
  _amount = RANGE_AMOUNT;
}

RangeItem::~RangeItem()
{
}

void	RangeItem::setAttr(ACharacter *ch) const
{
  ch->setRange(ch->getRange() + _amount);
  _gameInfo->sound->play("getbomb", EFFECT);
  increaseScore(ch);
}

AItem	*RangeItem::clone(int x, int y)
{
  return (new RangeItem(x, y, _gameInfo));
}
