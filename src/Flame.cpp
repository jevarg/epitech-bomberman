#include "Flame.hpp"

Flame::Flame(int x, int y, IObject *model, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, model, gameInfo)
{
}

Flame::~Flame()
{
}

void	Flame::hurtCharacter(ACharacter *character)
{
  character->setHealth(character->getHealth() - 0);
}

void	Flame::update(t_gameinfo &gameInfo)
{
  (void)gameInfo;
}
