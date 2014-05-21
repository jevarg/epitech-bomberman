#include "Box.hpp"
#include "ALivingEntity.hpp"

Box::Box(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOX, NULL, gameInfo)
{
}

Box::~Box()
{
}

void	Box::update(t_gameinfo &gameInfo)
{

}

void	Box::die()
{
  // may drop a bonus
  delete(this);
}
