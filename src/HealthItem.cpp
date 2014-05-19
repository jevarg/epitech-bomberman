#include "HealthItem.hpp"

HealthItem::HealthItem() : AItem()
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
