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

bool	AItem::checkItemColision(Map &map)
{
  AEntity *ent;

  if ((ent = map.getEntityIf(_x, _y, CHARACTER)) == NULL)
    return (false);
  setAttr(dynamic_cast<ACharacter *>(ent));
  destroy(map);
  return (true);
}

void	AItem::update()
{
  if (checkItemColision(_gameInfo.map) == true)
    return ;
  if (_timeout != NO_TIMEOUT)
    {
      --_timeout;
      if (_timeout == 0)
	{
	  destroy(_gameInfo.map);
	  return ;
	}
    }
}

void	AItem::takeDamages(int /*amount*/)
{
  _toDestroy = true;
  destroy(_gameInfo.map);
}
