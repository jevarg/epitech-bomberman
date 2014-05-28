#include "HealthItem.hpp"

HealthItem::HealthItem(int x, int y, t_gameinfo &gameInfo) :
  AItem(x, y, HEALTHITEM, gameInfo)
{
  _amount = HEALTH_AMOUNT;
}

HealthItem::~HealthItem()
{
}

void	HealthItem::setAttr(ACharacter *ch) const
{
  ch->setHealth(ch->getHealth() + _amount);
}

AItem	*HealthItem::clone(int x, int y)
{
  return (new HealthItem(x, y, _gameInfo));
}
