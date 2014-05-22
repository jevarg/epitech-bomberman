#include "HealthItem.hpp"

HealthItem::HealthItem(int x, int y, eType type) :
  AItem(x, y, type)
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
