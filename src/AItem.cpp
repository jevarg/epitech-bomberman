#include "GameEngine.hpp"
#include "AItem.hpp"

AItem::AItem(int x, int y, eType type, t_gameinfo &gameInfo) :
  ALivingEntity(x, y, type, gameInfo)
{
  _timeout = NO_TIMEOUT;
  _amount = 0;
}

AItem::~AItem()
{
}

void	AItem::update()
{
}

void	AItem::takeDamages(int /*amount*/)
{
  _toDestroy = true;
  destroy(_gameInfo.map);
}

void	AItem::destroy(Map &map)
{
  map.removeEntityByPtr(this);
  delete (this);
}
