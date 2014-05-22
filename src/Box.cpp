#include "Box.hpp"
#include "ALivingEntity.hpp"

Box::Box(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOX, gameInfo)
{
}

Box::~Box()
{
}

void	Box::update(t_gameinfo &gameInfo)
{
}

void	Box::update()  // a virer apres le merge qui change la classe mere de Box
{
}

void	Box::die()
{
  // may drop a bonus
  delete(this);
}
