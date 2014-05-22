#include "HealthItem.hpp"

HealthItem::HealthItem(int x, int y, eType type, t_gameinfo &gameInfo) :
  AItem(x, y, type, gameInfo)
{
  _amount = HEALTH_AMOUNT;
}

HealthItem::~HealthItem()
{
}

void	HealthItem::setHealth(ACharacter &ch)
{
  ch.setHealth(ch.getHealth() + _amount);
}
