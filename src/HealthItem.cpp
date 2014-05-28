#include "HealthItem.hpp"

HealthItem::HealthItem(int x, int y, eType type, t_gameinfo &gameInfo) :
  AItem(x, y, type, gameInfo)
{
  _amount = HEALTH_AMOUNT;
}

HealthItem::~HealthItem()
{
}

void	HealthItem::setAttr(ACharacter *ch) const
{
  if (ch->getHealth() < HEALTH_MAX)
    ch->setHealth(ch->getHealth() + _amount);
}
