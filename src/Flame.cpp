#include "Flame.hpp"

Flame::Flame(int x, int y, IObject *model)
  : AEntity(x, y, FLAME, model), _mutex(), _condvar()
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
