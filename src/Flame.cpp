#include "Flame.hpp"

Flame::Flame(IObject *model)
  : AEntity(0, 0, FLAME, model), _mutex(), _condvar()
{
}

Flame::~Flame()
{
}

void	Flame::hurtCharacter(ACharacter *character)
{
  character->hit();
}
