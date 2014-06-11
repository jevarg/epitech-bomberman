#include "GameEngine.hpp"
#include "HealthItem.hpp"

HealthItem::HealthItem(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, HEALTHITEM, gameInfo, thread)
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
  increaseScore(ch);
  _gameInfo->sound->playSound("eat");
}

AItem	*HealthItem::clone(int x, int y)
{
  return (new HealthItem(x, y, _gameInfo));
}
