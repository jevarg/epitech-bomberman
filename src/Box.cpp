#include "Box.hpp"
#include "ALivingEntity.hpp"

Box::Box(int x, int y, eType type, t_gameinfo &gameInfo)
  : AEntity(x, y, type, gameInfo)
{
}

Box::~Box()
{
}

void	Box::takeDamages(int)
{
}

void	Box::destroy(Map &map)
{
  (void)map;
}
