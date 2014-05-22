#include "Flame.hpp"

Flame::Flame(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, gameInfo)
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
